/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:13:29 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:47:17 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the index of the single quotes
 * without going in the double quotes
 * 
 * @test works with input '"'"'"
 * 
 * @param str
 * @return int* return a list of index where the single quotes are
 */
int	*get_index_single_quotes(char *str)
{
	int	i;
	int	*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	ret[0] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			ret = append_int(ret, i);
			while (str[i + 1] && str[++i] != '\'')
				;
			ret = append_int(ret, i);
		}
		else if (str[i] == '\"')
		{
			while (str[i + 1] && str[++i] != '\"')
				;
		}
	}
	return (ret);
}

int	*get_index_double_quotes(char *str)
{
	int	i;
	int	*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	ret[0] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			ret = append_int(ret, i);
	}
	return (ret);
}

int	*get_index_white_space(char *str)
{
	int	i;
	int	*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	ret[0] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || (str[i] <= '\t' && str[i] >= '\r'))
		{
			ret = append_int(ret, i);
			while (str[i] == ' ' || (str[i] <= '\t' && str[i] >= '\r'))
				i++;
			ret = append_int(ret, i);
			if (!str[i])
				i--;
		}
	}
	return (ret);
}

int	*get_index_pipe(char *str)
{
	int	i;
	int	*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	ret[0] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			ret = append_int(ret, i);
			i++;
			ret = append_int(ret, i);
		}
		if (!str[i])
			i--;
	}
	return (ret);
}

int	*get_index_redirect(char *str)
{
	int		i;
	int		*ret;
	char	c;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[0] = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			ret = append_int(ret, i);
			c = str[i];
			while (str[i] && str[i] == c)
				i++;
			ret = append_int(ret, i);
			i--;
		}
	}
	return (ret);
}
