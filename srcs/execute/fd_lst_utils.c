/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:11 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/11 18:04:16 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	fd_lst_add_front(t_fd_lst **lst, t_fd_lst *new)
{
	if (!lst || !new)
		return (1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	new->next = *lst;
	*lst = new;
	return (0);
}

t_fd_lst	*fd_lst_new(int fd)
{
	t_fd_lst	*new;

	new = malloc(sizeof(t_fd_lst));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}
