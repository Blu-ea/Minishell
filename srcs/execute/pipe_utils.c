/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:29:54 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/13 18:17:23 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_pipe	*pipe_last(t_pipe *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pipe	*pipe_new(char **args, int *fd)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->args = args;
	if (fd)
	{
		new->fd[0] = fd[0];
		new->fd[1] = fd[1];
	}
	new->next = NULL;
	return (new);
}

char	pipe_add_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*last;

	if (!lst || !new)
		return (1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	last = pipe_last(*lst);
	last->next = new;
	return (0);
}
