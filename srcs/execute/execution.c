/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:47:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/19 16:38:21 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/**
 * @brief SAFE Open a pipe and a fork safely
 * 
 * @param pipefd: list of the stdin and stdout of the pipe
 * @param args: list of args to free in case it fails
 * @param std_ins: list of the stdin to free in case it fails
 * @param pids: list of the pid to free in case it fails
 * @return the pid of the child or -1 if the command had an error
 */
pid_t	open_fork(int pipefd[2], t_pipe *pip, t_fd_lst *std_ins, t_fd_lst *pids)
{
	pid_t	pid;

	if (pip->args[0] == 0)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		clear_pipe_lst(pip, 1);
		free_fds(std_ins, pids);
		ft_exit("Pipe error: ", 1);
	}
	pid = fork();
	if (pid == -1)
	{
		clear_pipe_lst(pip, 1);
		free_fds(std_ins, pids);
		ft_exit("Fork error: ", 1);
	}
	return (pid);
}

/**
 * @brief Check if the command a path (begining with / or .) or dup the command
 * if it exist based on the dup parameter
 * 
 * @param str: the command to check/dup
 * @param dup: bool to dup or check the command
 * @return bool if the command a path or the dupped command
 */
char	*is_path_and_dup_access(char *str, char dup)
{
	if (!str[0] && dup)
		return (0);
	else if (!str[0] && !dup)
		return ((char *)1);
	if (dup)
	{
		if (str && access(str, F_OK) == 0)
			return (ft_strdup(str));
		return (0);
	}
	str = ft_strtrim(str, " \t\n\r");
	if (str[0] == '/' || (str[0] == '.' && str[1] == '/'))
	{
		free(str);
		return ((char *)1);
	}
	free(str);
	return (0);
}

/**
 * @brief Get the full path of the command
 * 
 * @param path: the path to search in
 * @param cmd: the command to search
 * @return the full path of the command or 0 if it doesn't exist
 */
char	*get_path(char *path, char *cmd, int i)
{
	char	*tmp;
	char	*new_path;
	char	**paths;

	if (is_path_and_dup_access(cmd, 0))
		return (is_path_and_dup_access(cmd, 1));
	paths = ft_split(path, ':');
	new_path = (char *)-1;
	while (paths && (new_path == (char *)-1 || access(new_path, F_OK)))
	{
		if (new_path != (char *)-1)
			free(new_path);
		if (new_path != 0 && paths && paths[++i])
		{
			new_path = ft_strjoin(paths[i], "/");
			tmp = new_path;
			new_path = ft_strjoin(new_path, cmd);
			free(tmp);
		}
		else if (paths)
			return (clear_split(paths));
	}
	clear_split(paths);
	return (new_path);
}

/**
 * @brief Duplicate the appropriate fd to the stdin and stdout and execute the
 * command
 * 
 * @param pipefd[2]: stdin and stdout of the pipe
 * @param pipe: the pipe to execute
 * @param envp: the envp
 * @param std_ins: the list of the stdin to get the output of the previous pipe
 * @return the error code of the execve or 0 if the command doesn't exist or if
 * there was a malloc error
 */
int	handle_child(int *pipefd, t_pipe *pipe, char **envp, t_fd_lst **std_ins)
{
	int		i;
	char	*path;

	close(pipefd[0]);
	if (pipe->fd[0] != 0)
		dup2(pipe->fd[0], STDIN_FILENO);
	else
		dup2((*std_ins)->fd, STDIN_FILENO);
	if (pipe->fd[1] != 1 && pipe->next->next)
		dup2(pipe->fd[1], STDOUT_FILENO);
	else if (pipe->next->next)
		dup2(pipefd[1], STDOUT_FILENO);
	path = get_path(getenv("PATH"), pipe->args[0], -1);
	if (path && path != (char *)-1)
	{
		i = execve(path, pipe->args, envp);
		free(path);
	}
	else
	{
		i = -(path == (char *)-1);
		close(pipefd[1]);
	}
	return (i);
}

int	launch_prog(t_pipe *pipe, char **envp, t_fd_lst **std_ins, t_fd_lst **pids)
{
	pid_t	pid;
	int		pipefd[2];

	pid = open_fork(pipefd, pipe, *std_ins, *pids);
	if (pid == 0)
	{
		return (handle_child(pipefd, pipe, envp, std_ins));
	}
	else if (pid == -1)
		return (0);
	close(pipefd[1]);
	if (fd_lst_add_front(std_ins, fd_lst_new(pipefd[0])))
		return (-1);
	return (pid);
}
