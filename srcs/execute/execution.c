/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:47:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 14:09:29 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

int	ft_execve(char *path, t_pipe *pipe, char **envp);

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
			new_cmd = ft_strjoin_free(ft_strjoin(paths[i], "/"), *cmd, FREE_S1);
		else if (paths)
			return (clear_split(paths));
	}
	*path = new_cmd;
	return (clear_split(paths), 1);
}

/**
 * @brief Check if the command is a built in and execute it or execute the
 * command
 * 
 * @param path: the path to the command or 0 if it doesn't exist or if there was
 * an error
 * @param pipe: the pipe to execute
 * @param envp: the environment
 * @return 0 if the command doesn't exist or if there was a malloc error or the
 * negative of the return value -1 of the command if it's a built in or -257 if
 * the execve failed or -258 if the command is a directory
 */
int	execute(char *path, t_pipe *pipe, char **envp)
{
	int	i;

	i = is_built_in(pipe->args[0]);
	if (i)
	{
		i = run_built_in(i, &pipe, &envp, 0);
		if (path)
			free(path);
		clear_split(envp);
		return (-i - 1);
	}
	if (path)
		return (ft_execve(path, pipe, envp));
	else
		clear_split(envp);
	return (0);
}

int	ft_execve(char *path, t_pipe *pipe, char **envp)
{
	struct stat	path_stat;
	int			ret;

	stat(path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		errno = EISDIR;
		ft_print_error(pipe->args[0]);
		ret = -258;
	}
	else
	{
		ret = execve(path, pipe->args, envp) * 257;
		clear_split(envp);
	}
	free(path);
	return (ret);
}
