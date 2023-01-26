/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:39:52 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 00:01:32 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!pipes)
		return (1);
	i = -1;
	while (pipes[++i])
		clear_pipe(pipes[i]);
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

char	free_return(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}
