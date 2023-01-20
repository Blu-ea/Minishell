/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:28:01 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:50:16 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_empty(char ***cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (cmd && cmd[0] && cmd[0][++i])
	{
		if (cmd[0][i][0] == '0' && cmd[0][i][1] == '\0')
		{
			tmp = cmd[0][i];
			j = i;
			while (cmd[0][j])
			{
				cmd[0][j] = cmd[0][j + 1];
				j++;
			}
			free(tmp);
		}
	}
}
