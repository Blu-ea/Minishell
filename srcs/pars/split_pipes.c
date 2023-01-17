/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:04:25 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/16 19:14:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_cmd(char **cmd, char **pipe)
{
	int	i;

	i = -1;
	while (*cmd)
	{
		if (**cmd == '4')
		{
			free(*cmd++);
			break ;
		}
		else
			pipe[++i] = *cmd;
		cmd++;
	}
	pipe[++i] = NULL;
	return (cmd);
}

char	***split_pipes(char **cmd)
{
	int		i;
	int		nb_pipes;
	char	**ori;
	char	***pipes;

	clean_empty(&cmd);
	ori = cmd;
	nb_pipes = number_of_pipes(cmd) + 1;
	pipes = malloc(sizeof(*pipes) * (nb_pipes + 1));
	if (!pipes)
		return (NULL); // FIXME: free on error
	i = -1;
	while (++i < nb_pipes)
	{
		pipes[i] = malloc(sizeof(*(pipes[i])) * (size_pipe(cmd, i) + 1));
		if (!pipes[i])
			return (clear_error_pipes(pipes, cmd, i - 1));
	}
	i = -1;
	while (++i < nb_pipes)
		cmd = sort_cmd(cmd, pipes[i]);
	pipes[i] = NULL;
	free(ori);
	return (pipes);
}
