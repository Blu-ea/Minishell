/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:41:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:45:56 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	handle_double_quotes(char ***cmd)
{
	int	i;
	int	j;
	int	*cutting_indexs;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_double_quotes(cmd[0][i] + 1);
			if (!cutting_indexs)
				return (1);
			j = split_merge_cmd(cmd, cutting_indexs, i, cut_command);
			free(cutting_indexs);
			if (j == -1)
				return (1);
			i += j - 1;
		}
	}
	return (0);
}

char	handle_white_space(char ***cmd)
{
	int	i;
	int	j;
	int	*cutting_indexs;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_white_space(cmd[0][i] + 1);
			if (!cutting_indexs)
				return (1);
			j = split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_space);
			free(cutting_indexs);
			if (j == -1)
				return (1);
			i += j - 1;
		}
	}
	return (0);
}

char	handle_redirect(char ***cmd)
{
	int	i;
	int	j;
	int	*cutting_indexs;

	i = -1;
	while (cmd && cmd[0] && cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_redirect(cmd[0][i] + 1);
			if (!cutting_indexs)
				return (1);
			j = split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_redirect);
			free(cutting_indexs);
			if (j == -1)
				return (1);
			i += j - 1;
		}
	}
	return (0);
}

char	handle_pipes(char ***cmd)
{
	int	i;
	int	j;
	int	*cutting_indexs;

	i = -1;
	while (cmd && cmd[0] && cmd[0][++i])
	{
		if (cmd[0][i][0] == '0')
		{
			cutting_indexs = get_index_pipe(cmd[0][i] + 1);
			if (!cutting_indexs)
				return (1);
			j = split_merge_cmd(cmd, cutting_indexs, i, cut_cmd_pipe);
			free(cutting_indexs);
			if (j == -1)
				return (1);
			i += j - 1;
		}
	}
	return (0);
}
