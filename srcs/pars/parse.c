/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:42:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/21 00:47:26 by jcollon          ###   ########lyon.fr   */
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

int	number_of_pipes(char **str)
{
	int	ret;

	ret = 0;
	while (str && *str)
	{
		if (str[0][0] == '4')
			ret++;
		str++;
	}
	return (ret);
}

/**
 * @brief Preporcessing of the command line, it will return a list of pipes,
 * each pipe is a list of commands and each command is a list of arguments that
 * are identified by a special character at the beginning of the argument. (0
 * for a normal argument, 1 for arguments that where in quotes, 2 for spaces,
 * 3 for redirections, 4 for pipes(shoudn't be here))
 * 
 * @param str: the command line
 * @param env: the environment
 * @return A list of pipes or NULL if there is an error or 1 if there is a quote
 * error
 */
char	***parse(char *str, char **env)
{
	char	***tmp;
	char	**cmd;
	int		*cutting_indexs;
	int		i;

	if (quote_error(str))
		return ((char ***)1);
	cutting_indexs = get_index_single_quotes(str);
	if (!cutting_indexs)
		return (NULL);
	cmd = cut_command(str, cutting_indexs);
	free(cutting_indexs);
	if (!cmd)
		return (NULL);
	if ((handle_dollar_variables(cmd, env) || handle_double_quotes(&cmd)
			|| handle_white_space(&cmd) || handle_pipes(&cmd)
			|| handle_redirect(&cmd)) && cmd && clear_pipe(cmd))
		return (NULL);
	tmp = split_pipes(cmd);
	i = -1;
	while (tmp && tmp[++i])
		trim_pipe(tmp + i);
	return (tmp);
}
