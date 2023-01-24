/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:19:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/24 19:00:57 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

void	read_heredoc(char *str, int fd, char **env);

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
	if (pipe_add_back(tpipe, pipe_new(0, 0, (*tpipe)->env)))
		return (1);
	*tpipe = (*tpipe)->next;
	return (0);
}

void	ft_fork_heredoc(int pipefd[2], char **str, t_pipe *pipe_lst,
	char ***pipes)
{
	close(pipefd[0]);
	pipe_lst->env = unset_del(pipe_lst->env, "?");
	read_heredoc((*str) + 1, pipefd[1], pipe_lst->env);
	close(pipefd[1]);
	clear_split(pipe_lst->env);
	clear_pipes(pipes);
	clear_pipe_lst(pipe_lst, 0);
	ft_clear_line(NULL, IN_EXIT);
	exit(0);
}
