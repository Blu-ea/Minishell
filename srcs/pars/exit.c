/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:39:52 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/17 17:54:42 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(const char *str)
{
	if (errno)
		perror(str);
	else
		ft_putendl_fd((char *)str, 2);
	exit(errno);
}

char	***clear_error_pipes(char ***pipes, char **cmd, int i)
{
	while (i >= 0)
	{
		free(pipes[i]);
		i--;
	}
	clear_pipe(cmd);
	free(pipes);
	return (NULL);
}

void	clear_pipe(char **pipe)

{
	int	j;

	if (!pipe)
		return ;
	j = -1;
	while (pipe[++j])
		free(pipe[j]);
	free(pipe);
}

void	clear_pipes(char ***pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (pipes[++i])
		clear_pipe(pipes[i]);
	free(pipes);
}
