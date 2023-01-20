/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:18:25 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:50:02 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_parts(char *str, int *indexs)
{
	int	ret;

	if (indexs[0] == -1)
		return (1);
	ret = ft_inttablen(indexs) - 1;
	if (indexs[0] != 0)
		ret++;
	if (indexs[ft_inttablen(indexs) - 1] != ft_strlen(str))
		ret++;
	return (ret);
}

char	**cut_command(char *str, int *indexs)
{
	char	**ret;
	int		i;
	int		j;

	if (ft_inttablen(indexs) % 2 != 0)
		return (NULL);
	ret = ft_calloc(sizeof(*ret), (cmd_parts(str, indexs) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	if (indexs[0] != 0)
		ret[j++] = add_prefix("0", ft_substr(str, 0, indexs[0]));
	while (indexs[i] != -1)
	{
		if ((j + (indexs[0] == 0)) % 2)
			ret[j++] = add_prefix("1", ft_substr(str, indexs[i] + 1,
						indexs[i + 1] - indexs[i] - 1));
		else if (indexs[i] != ft_strlen(str) - 1)
			ret[j++] = add_prefix("0", ft_substr(str, indexs[i] + 1,
						indexs[i + 1] - indexs[i] - 1));
		i++;
	}
	ret[j] = NULL;
	return (check_fail_cut_cmd(ret, j));
}

char	**cut_cmd_space(char *str, int *indexs)
{
	char	**ret;
	int		i;
	int		j;

	if (ft_inttablen(indexs) % 2 != 0)
		return (NULL);
	ret = ft_calloc(sizeof(*ret), (cmd_parts(str, indexs) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	if (indexs[0] != 0)
		ret[j++] = add_prefix("0", ft_substr(str, 0, indexs[0]));
	while (indexs[i] != -1)
	{
		if ((j + (indexs[0] == 0)) % 2)
			ret[j++] = add_prefix("2",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		else if (indexs[i] != ft_strlen(str))
			ret[j++] = add_prefix("0",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		i++;
	}
	ret[j] = NULL;
	return (check_fail_cut_cmd(ret, j));
}

char	**cut_cmd_pipe(char *str, int *indexs)
{
	char	**ret;
	int		i;
	int		j;

	if (ft_inttablen(indexs) % 2 != 0)
		return (NULL);
	ret = ft_calloc(sizeof(*ret), (cmd_parts(str, indexs) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	if (indexs[0] != 0)
		ret[j++] = add_prefix("0", ft_substr(str, 0, indexs[0]));
	while (indexs[i] != -1)
	{
		if ((j + (indexs[0] == 0)) % 2)
			ret[j++] = add_prefix("4",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		else if (indexs[i] != ft_strlen(str))
			ret[j++] = add_prefix("0",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		i++;
	}
	ret[j] = NULL;
	return (check_fail_cut_cmd(ret, j));
}

char	**cut_cmd_redirect(char *str, int *indexs)
{
	char	**ret;
	int		i;
	int		j;

	if (ft_inttablen(indexs) % 2 != 0)
		return (NULL);
	ft_calloc(sizeof(*ret), (cmd_parts(str, indexs) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	if (indexs[0] != 0)
		ret[j++] = add_prefix("0", ft_substr(str, 0, indexs[0]));
	while (indexs[i] != -1)
	{
		if ((j + (indexs[0] == 0)) % 2)
			ret[j++] = add_prefix("3",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		else if (indexs[i] != ft_strlen(str))
			ret[j++] = add_prefix("0",
					ft_substr(str, indexs[i], indexs[i + 1] - indexs[i]));
		i++;
	}
	ret[j] = NULL;
	return (check_fail_cut_cmd(ret, j));
}
