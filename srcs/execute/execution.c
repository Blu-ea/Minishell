/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:47:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 01:32:48 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

/**
 * @brief Check if the command a path (begining with / or .)
 * 
 * @param str: the command to check/dup
 * @param env: the env to get the home path
 * @return bool if the command a path
 */
char	is_path(char **str, char **env)
{
	char	*tmp;

	if (!*str[0])
		return (1);
	if (*str && (*str[0] == '/' || *str[0] == '.' || *str[0] == '~'))
	{
		if (*str[0] == '~')
		{
			tmp = *str;
			*str = follow_home(*str, env, NULL);
			free(tmp);
		}
		return (1);
	}
	return (0);
}

/**
 * @brief Check if the command exist and is a file
 * 
 * @param str: the command to check
 * @return The dupped command or 0 if it doesn't exist or is not a file or -1 if
 * an error occured or HOME is not set and it was a path with ~
 */
char	check_access(char *str, char **cmd)
{
	if (!str)
	{
		free(*cmd);
		return (-1);
	}
	if (!str[0])
	{
		free(*cmd);
		return (0);
	}
	if (str && (access(str, F_OK) == 0 || is_built_in(str)))
	{
		free(*cmd);
		*cmd = ft_strdup(str);
		return (1);
	}
	free(*cmd);
	return (0);
}

/**
 * @brief Get the full path of the command
 * 
 * @param path: the address of the path variable
 * @param cmd: the command to check
 * @param env: the environment to get $HOME
 * @return 1 if the command exist or 0 if it doesn't exist or -1 if an error
 * occured and put the full path in path
 */
char	get_path(char **path, char **cmd, char **env)
{
	char	*tmp;
	char	*new_cmd;
	char	**paths;
	int		i;

	if (is_path(cmd, env) || is_built_in(*cmd))
		return (check_access(*cmd, path));
	if (!*path)
		return (0);
	paths = ft_split(*path, ':');
	free(*path);
	if (!paths)
		return (-1);
	new_cmd = NULL;
	i = -1;
	while (paths && (new_cmd == NULL || access(new_cmd, F_OK)))
	{
		if (new_cmd)
			free(new_cmd);
		if (paths && paths[++i])
		{
			new_cmd = ft_strjoin(paths[i], "/");
			tmp = new_cmd;
			new_cmd = ft_strjoin(new_cmd, *cmd);
			if (tmp)
				free(tmp);
		}
		else if (paths)
			return (clear_split(paths));
	}
	clear_split(paths);
	*path = new_cmd;
	return (1);
}

/**
 * @brief Check if the command is a built in and execute it or execute the
 * command
 * 
 * @param path: the path to the command or 0 if it doesn't exist or -1 if there
 * was a malloc error
 * @param pipe: the pipe to execute
 * @param envp: the environment
 * @return -1 if execve failed or 0 if the command doesn't exist or -256 if
 * there was a malloc error
 */
int	execute(char *path, t_pipe *pipe, char **envp)
{
	struct stat	path_stat;
	int			i;

	i = is_built_in(pipe->args[0]);
	if (i)
	{
		i = run_built_in(i, &pipe, &envp, 0);
		if (path && path != (char *)-1)
			free(path);
		clear_split(envp);
		ft_clear_line(NULL, IN_EXIT);
		exit(i);
	}
	if (path && path != (char *)-1)
	{
		stat(path, &path_stat);
		if (!S_ISREG(path_stat.st_mode))
		{
			errno = EISDIR;
			ft_print_error(pipe->args[0]);
			i = -126;
		}
		else
		{
			// g_error_sig = CHILD;
			i = execve(path, pipe->args, envp);
			clear_split(envp);
		}
		free(path);
		return (i);
	}
	if (!path)
		clear_split(envp);
	else if (path != (char *)-1)
		free(path);
	i = -((path == (char *)-1) * 256);
	return (i);
}

/**
 * @brief Duplicate the appropriate fd to the stdin and stdout and execute the
 * command
 * 
 * @param pipefd[2]: stdin and stdout of the pipe
 * @param pipe: the pipe to execute
 * @param envp: the envp
 * @param std_ins: the list of the stdin to get the output of the previous pipe
 * @return the error code of the execve or 0 if the command doesn't exist or
 * -256 if there was a malloc error
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
		ret = -2;
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
 * @return the pid of the child or 0 if the command doesn't exist or -256 if
 * there was a malloc error or a negative number if there was an error and the
 * absolute value is the error code of the execve
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
