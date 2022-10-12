/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/12 18:34:00 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_export(char *s);
int		ft_issallgood_export(char *s);

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNSET or ENV_SET 
 * 	Return -1 if the name is not valuale Not implemented yet or crash
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	char	*temp;
	int		i;

	i = 0;
	temp = split_export(name);
	if (!temp)
		return (-1);
	if (temp == 0)
		return (-2);
	if (ft_issallgood_export(temp))
		return (-2);
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			if (env[i][ft_strlen(temp)] == '=')
			{
				free(temp);
				return (ENV_SET);
			}
		}
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			if (env[i][ft_strlen(temp)] == 0)
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

int	ft_issallgood_export(char *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s[i]) && s[i] != '_')
		return (EXIT_FAILURE);
	while (s[i])
	{
		if (s[i] != '_' && ft_isalphanum(s[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*split_export(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '=' && s[i] != 0)
		i++;
	if (s[i] == 0)
		return (ft_strdup(s));
	if (s[i - 1] == '+')
		return (ft_strndup(s, i - 1));
	return (ft_strndup(s, i));
}

// char	**env_init(char **env)
// {}
