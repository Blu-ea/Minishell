/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:02:35 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/18 14:43:58 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/**
 * @brief Free the list of args and the pointer to args if clear_args is 1.
 * it skips the first arg if it's NULL (because redirect failed)
 * 
 * @param pipe: The list of t_pipe
 * @param clear_args: If 1, free the args
 */
void	clear_pipe_lst(t_pipe *pipe, char clear_args)
{
	t_pipe	*tmp;
	int		i;

	while (pipe && pipe->next)
	{
		i = -1;
		if (clear_args)
		{
			if (pipe->args[0] == NULL)
				i++;
			while (pipe->args[++i])
				free(pipe->args[i]);
			free(pipe->args);
		}
		if (pipe->fd[0] != 0)
			close(pipe->fd[0]);
		if (pipe->fd[1] != 1)
			close(pipe->fd[1]);
		tmp = pipe;
		pipe = pipe->next;
		free(tmp);
	}
	free(pipe);
}

/**
 * @brief Free a split
 * 
 * @param split: The split to free
 * @return NULL
 */
void	*clear_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (NULL);
}

/**
 * @brief Free pipe_lst and pipes
 * 
 * @param pipe_lst 
 * @param pipes 
 * @return 1 or errno if errno is set
 */
char	clear_error_pipe(t_pipe *pipe_lst, char ***pipes)
{
	clear_pipes(pipes);
	clear_pipe_lst(pipe_lst, 0);
	if (errno)
		return (errno);
	return (1);
}
