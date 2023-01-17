/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:42:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/17 17:55:49 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	quote_error(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
			{
				if (*str == '\0')
					return (1);
				str++;
			}
		}
		if (*str == '\"')
		{
			str++;
			while (*str != '\"')
			{
				if (*str == '\0')
					return (1);
				str++;
			}
		}
		str++;
	}
	return (0);
}

/**
 * @brief Replace all white spaces by 1 space char
 * 
 * @param str 
 * @return char* 
 */
char	*clear_white_space(char *str)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ' || (str[i] <= '\t' && str[i] >= '\r'))
		{
			ret[j++] = ' ';
			while (str[i] == ' ' || (str[i] <= '\t' && str[i] >= '\r'))
				i++;
			i--;
		}
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

int	number_of_pipes(char **str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (str[0][0] == '4')
			ret++;
		str++;
	}
	return (ret);
}

char	***parse(char *str, char **env)
{
	char	**cmd;
	int		*cutting_indexs;

	if (quote_error(str))
		return (NULL);
	cutting_indexs = get_index_single_quotes(str);
	if (!cutting_indexs)
		return (NULL);
	cmd = cut_command(str, cutting_indexs);
	free(cutting_indexs);
	handle_dollar_variables(cmd, env);
	handle_double_quotes(&cmd);
	handle_white_space(&cmd);
	handle_pipes(&cmd);
	handle_redirect(&cmd);
	return (split_pipes(cmd));
}
