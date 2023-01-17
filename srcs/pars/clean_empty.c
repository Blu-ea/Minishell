/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:28:01 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/16 19:14:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_empty(char ***cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (cmd[0][++i])
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
