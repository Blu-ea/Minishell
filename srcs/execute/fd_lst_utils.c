/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:11 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/26 16:37:31 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	fd_lst_add_front(t_fd_lst **lst, t_fd_lst *new_lst)
{
	if (!lst || !new_lst)
		return (1);
	if (!*lst)
	{
		*lst = new_lst;
		return (0);
	}
	new_lst->next = *lst;
	*lst = new_lst;
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

t_fd_lst	*fd_lst_del_one(t_fd_lst *lst)
{
	t_fd_lst	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst->next;
	free(lst);
	return (tmp);
}
