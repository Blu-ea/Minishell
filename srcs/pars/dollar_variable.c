/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:19:17 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/26 17:44:42 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (!ft_isalpha(str[i]) || str[i] == '_'))
	{
		i++;
		while (str[i] && (!ft_isalphanum(str[i]) || str[i] == '_'))
			i++;
	}
	else if (str[i] && !ft_isdigit(str[i]))
		return (ft_substr(str, 0, 1));
	if (str[0] == '?')
		i = 1;
	if (i == 0)
		return (ft_strdup(""));
	return (ft_substr(str, 0, i));
}

/**
 * @brief Replace all $ variable by their value or empty string if not found 
 * 
 * @param str
 * @return char* 
 */
char	*handle_dollar_variable(char *str, char **env)
{
	int			i;
	int			len_var;
	char		*var;
	char		*tmp;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			tmp = get_variable(str + i + 1);
			len_var = ft_strlen(tmp);
			var = env_get_value(env, tmp);
			free(tmp);
			if (!var)
				var = ft_strdup("");
			tmp = ft_join3(ft_substr(str, 0, i), var, ft_substr(str,
						i + 1 + len_var, ft_strlen(str)));
			free(str);
			free(var);
			str = tmp;
		}
	}
	return (str);
}

char	handle_dollar_variables(char **cmd, char **env)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '0')
		{
			cmd[i] = handle_dollar_variable(cmd[i], env);
			if (!cmd[i])
				return (1);
		}
	}
	return (0);
}
