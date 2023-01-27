/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:42:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 02:01:56 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**handle_single_quotes(char *str)
{
	int		*cutting_indexs;
	char	**cmd;

	cutting_indexs = get_index_single_quotes(str);
	if (!cutting_indexs)
		return (NULL);
	cmd = cut_command(str, cutting_indexs);
	free(cutting_indexs);
	return (cmd);
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
 * @return A list of pipes or NULL if there is an error
 */
char	***parse(char *str, char **env)
{
	char	***tmp;
	char	**cmd;
	int		i;

	if (precheck(str))
		return (NULL);
	cmd = handle_single_quotes(str);
	if (!cmd)
		return (NULL);
	if ((handle_dollar_variables(cmd, env) || handle_double_quotes(&cmd)
			|| handle_white_space(&cmd) || handle_pipes(&cmd)
			|| handle_redirect(&cmd)) && cmd && clear_pipe(cmd))
		return (NULL);
	tmp = split_pipes(cmd);
	i = -1;
	while (tmp && tmp[++i])
		if (trim_pipe(tmp + i) && tmp && clear_pipes(tmp))
			return (NULL);
	return (tmp);
}
