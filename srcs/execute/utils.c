/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:19:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/19 15:49:08 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	remove_cmd(char **pipes)
{
	int		i;

	i = 0;
	free(pipes[i]);
	while (pipes[i + 1])
	{
		pipes[i] = pipes[i + 1];
		i++;
	}
	pipes[i] = NULL;
}

int	remove_redirect(char **pipe, int i)
{
	if (i && pipe[i - 1][0] == '2')
		remove_cmd(pipe + i-- - 1);
	remove_cmd(pipe + i);
	if (pipe[i] && pipe[i][0] == '2')
		remove_cmd(pipe + i);
	if (pipe[i])
		remove_cmd(pipe + i--);
	return (i);
}

char	disable_pipe(t_pipe **tpipe, char **pipe)
{
	free(*pipe);
	*pipe = NULL;
	(*tpipe)->args = pipe;
	(*tpipe)->next = NULL;
	if (pipe_add_back(tpipe, pipe_new(0, 0)))
		return (1);
	*tpipe = (*tpipe)->next;
	return (0);
}
