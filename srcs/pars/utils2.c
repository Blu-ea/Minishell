/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:28:33 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/20 23:33:57 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_pipe(char **pipe, int index)
{
	int	i;
	int	j;

	j = 0;
	index++;
	while (--index)
	{
		while (pipe[j] && pipe[j][0] != '4')
			j++;
		j++;
	}
	i = 0;
	while (pipe[i + j] && pipe[i + j][0] != '4')
		i++;
	return (i);
}

int	split_merge_cmd(char ***pipe, int *indexs, int index,
	char **(*cut)(char *, int *))
{
	int		len;
	int		i;
	char	**tmp;
	char	**tmp2;

	if (indexs[0] == -1 || ft_inttablen(indexs) % 2 != 0)
		return (1);
	tmp = cut(pipe[0][index] + 1, indexs);
	if (!tmp)
		return (-1);
	len = ft_tablen(tmp);
	i = 0;
	while (tmp[i + 1])
	{
		tmp2 = insert(*pipe, ft_strdup(tmp[i]), index + i);
		if (!tmp2 && clear_pipe(tmp))
			return (-1);
		*pipe = tmp2;
		i++;
	}
	free(pipe[0][index + i]);
	pipe[0][index + i] = ft_strdup(tmp[i]);
	clear_pipe(tmp);
	return (len);
}
