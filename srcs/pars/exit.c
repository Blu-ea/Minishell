/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:39:52 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:47:40 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exit the program with a message to the appropriate std, if errno is
 * set, print the error message
 * 
 * @param str: The message to print
 * @param exit_code: The exit code
 */
void	ft_exit(const char *str, int exit_code)
{
	if (str && exit_code)
	{
		ft_putstr_fd((char *)str, 2);
		if (errno)
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (str)
	{
		ft_putstr_fd((char *)str, 1);
		if (errno)
			ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
	}
	exit(exit_code);
}

char	***clear_error_pipes(char ***pipes, char **cmd, int i)
{
	while (i >= 0)
	{
		free(pipes[i]);
		i--;
	}
	clear_pipe(cmd);
	if (pipes)
		free(pipes);
	return (NULL);
}

/**
 * @brief Free a pipe
 * 
 * @param pipe: The pipe to free
 * @return 1 or errno if errno is set
 */
int	clear_pipe(char **pipe)
{
	int	i;

	i = 0;
	if (!pipe[0])
		i++;
	while (pipe[i])
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
	if (errno)
		return (errno);
	return (1);
}

/**
 * @brief Free pipes
 * 
 * @param pipes: The list of pipes
 * @return 1 or errno if errno is set
 */
int	clear_pipes(char ***pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		clear_pipe(pipes[i]);
		i++;
	}
	free(pipes);
	if (errno)
		return (errno);
	return (1);
}

char	**check_fail_cut_cmd(char **ret, int j)
{
	int	i;

	i = j;
	while (--j != -1)
	{
		if (!ret[j])
		{
			while (i--)
				free(ret[i]);
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}
