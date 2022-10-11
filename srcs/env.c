/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/11 18:55:24 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNSET or ENV_SET 
 * 	Return -1 if the name is not valuale Not implemented yet or crash
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(name, '=');
	if (!temp)
		return (-1);
	if (temp[0][ft_strlen(temp[0])] == '+')
		temp[0][ft_strlen(temp[0])] = 0;
	if (temp[0][0] != '_' && ft_isalpha(temp[0][0]))
		return (-2);	//need a print on that bad boy
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp[0], ft_strlen(temp[0])))
		{
			if (env[i][ft_strlen(temp[0])] == '=')
			{
				free(temp);
				return (ENV_SET);
			}
		}
		if (!ft_strncmp(env[i], temp[0], ft_strlen(temp[0])))
		{
			if (env[i][ft_strlen(temp[0])] == 0)
			{
				free(temp);
				return (ENV_NOTSET);
			}
		}
		i++;
	}
	free(temp);
	return (ENV_NOTSET);
}

// char	**env_init(char **env)
// {}
