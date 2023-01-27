/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:07:13 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 10:51:37 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

char	get_path(char **path, char **cmd, char **env);
int		execute(char *path, t_pipe *pipe, char **envp);

/**
 * @brief Duplicate the appropriate fd to the stdin and stdout and execute the
 * command
 * 
 * @param pipefd[2]: stdin and stdout of the pipe
 * @param pipe: the pipe to execute
 * @param envp: the envp
 * @param std_ins: the list of the stdin to get the output of the previous pipe
 * @return 0 if the command doesn't exist or if there was a malloc error or the
 * negative value of the return value of the bulitin -1 or -257 if there was a
 * execve error
 */
int	handle_child(int *pipefd, t_pipe *pipe, char **envp, t_fd_lst **std_ins)
{
	char	*path;
	int		ret;

	ret = 0;
	close(pipefd[0]);
	if (pipe->fd[0] != 0)
		dup2(pipe->fd[0], STDIN_FILENO);
	else if (*std_ins)
		dup2((*std_ins)->fd, STDIN_FILENO);
	if (pipe->fd[1] != 1)
		dup2(pipe->fd[1], STDOUT_FILENO);
	else if (pipe->next->next)
		dup2(pipefd[1], STDOUT_FILENO);
	path = env_get_value(envp, "PATH");
	if (get_path(&path, pipe->args, envp) == 1)
		ret = execute(path, pipe, envp);
	else
		clear_split(envp);
	if (!pipe->args[0])
	{
		pipe->args[0] = ft_strdup("");
		ret = -259;
	}
	close(pipefd[1]);
	return (ret);
}

/**
 * @brief Launch the program and add the stdin of the pipe to the list of stdin
 *  
 * @param pipe: the pipe to execute 
 * @param envp: the envp
 * @param std_ins: the list of the stdin to get the output of the previous pipe
 * and add the stdin of the current pipe
 * @return the pid of the child or 0 if the command doesn't exist or if there
 * was a malloc error or a negative number if there was an error and the
 * absolute value is the error code of the bultin -1 or -257 if there was a
 * execve error
 */
int	launch_prog(t_pipe *pipe, char **envp, t_fd_lst **std_ins)
{
	pid_t	pid;
	int		pipefd[2];

	pid = open_fork(pipefd, pipe);
	if (pid == 0)
	{
		envp = unset_del(envp, "?");
		return (handle_child(pipefd, pipe, envp, std_ins));
	}
	else if (pid == -1)
		return (0);
	close(pipefd[1]);
	if (fd_lst_add_front(std_ins, fd_lst_new(pipefd[0])))
		return (-256);
	return (pid);
}
