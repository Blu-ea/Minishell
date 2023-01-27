/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:21:36 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 02:02:32 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if every quote is closed
 * 
 * @param str: The string to check
 * @return 0 if no error, 1 if ' is unclosed, 2 if " is unclosed
 */
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
					return (2);
				str++;
			}
		}
		str++;
	}
	return (0);
}

/**
 * @brief Check if there are empty pipes
 * 
 * @param str: The string to check
 * @return 0 if no error, 1 if there is an empty pipe
 */
char	pipe_error(char *str)
{
	int	i;

	str = ft_strtrim(str, " \t\v\f\r");
	if (!str)
		return (1);
	if (str[0] == '|')
		return (free_return(str, 1));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			while (str[++i] && (str[i] == ' ' || str[i] == '\t'
					|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
				;
			if (str[i] == '|')
				return (free_return(str, 1));
			if (str[i] == '\0')
				return (free_return(str, 1));
		}
	}
	return (free_return(str, 0));
}

char	precheck(char *str)
{
	char	tmp;

	tmp = quote_error(str);
	if (tmp == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `\''\n", 2);
	if (tmp == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
	if (tmp)
		return (1);
	if (pipe_error(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}
