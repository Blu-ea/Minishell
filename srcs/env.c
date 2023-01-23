/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/23 18:51:29 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_export(char *s);
int		ft_issallgood_export(char *s);
int		env_is_set_ret(char *temp, int ret);

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNDIFINED or ENV_SET 
 * 	Return -1 if the name is not valuale Not implemented yet or crash
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	char	*temp;
	int		i;

	i = -1;
	temp = split_export(name);
	if (!temp || !env)
		return (-1);
	if (ft_issallgood_export(temp))
		return (-2);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			if (env[i][ft_strlen(temp)] == '=')
				return (env_is_set_ret(temp, ENV_SET));
			if (env[i][ft_strlen(temp)] == 0)
				return (env_is_set_ret(temp, ENV_UNDIFINED));
		}
	}
	free(temp);
	return (ENV_NOTSET);
}

int	env_is_set_ret(char *temp, int ret)
{
	free(temp);
	return (ret);
}

int	ft_issallgood_export(char *s)
{
	int	i;

	i = 0;
	if (!ft_isdigit(s[i]) && s[i] != '_')
	{
		free(s);
		return (EXIT_FAILURE);
	}
	while (s[i])
	{
		if (s[i] != '_' && ft_isalphanum(s[i]))
		{
			free(s);
			return (EXIT_FAILURE);
		}
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

/**
 * @brief Return the value of the env variable of name
 * 
 * @param env 
 * @param name 
 * @return NULL if the variable is not set
 */
char	*env_get_value(char **env, char *name)
{
	int		i;
	char	*ret;
	char	*temp;

	if (!env)
		return (NULL);
	i = -1;
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			ret = ft_strndup(env[i] + ft_strlen(temp), ft_strlen(env[i]));
			free(temp);
			return (ret);
		}
	}
	free(temp);
	return (NULL);
}

// char	**env_init(char **env)
// {}
