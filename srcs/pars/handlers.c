/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:41:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/16 19:14:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_quotes(char ***cmd)
{
	int	i;
	int	*cutting_indexs;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_double_quotes(cmd[0][i] + 1);
			i += split_merge_cmd(cmd, cutting_indexs, i, cut_command) - 1;
			free(cutting_indexs);
		}
	}
}

void	handle_white_space(char ***cmd)
{
	int	i;
	int	*cutting_indexs;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_white_space(cmd[0][i] + 1);
			i += split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_space) - 1;
			free(cutting_indexs);
		}
	}
}

char	handle_redirect(char ***cmd)
{
	int	*cutting_indexs;
	int	i;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_redirect(cmd[0][i] + 1);
			if (cutting_indexs[0] != -1
				&& cutting_indexs[0] - cutting_indexs[1] < -2)
			{
				free(cutting_indexs);
				return (1);
			}
			i += split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_redirect) - 1;
			free(cutting_indexs);
		}
	}
	return (0);
}

void	handle_pipes(char ***cmd)
{
	int *cutting_indexs;
	int	i;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_pipe(cmd[0][i] + 1);
			i += split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_pipe) - 1;
			free(cutting_indexs);
		}
	}
}
