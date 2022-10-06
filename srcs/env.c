/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 07:32:09 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_init(char **env)
{
}

char	**env_add(char **env, char *name, char *desc)
{
}

char	**env_sub(char **env, char *name)
{
}

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNSET or ENV_SET
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	int		i;
	char	*name_;

	i = 0;
	name_ = ft_strjoin(name, "=");
	while (env)
	{
		if (!ft_strncmp(*env, name_, ft_strlen(name_)))
			return (ENV_SET);
		if (!ft_strncmp(*env, name, ft_strlen(name)) && \
				*env[ft_strlen(name)] == 0)
			return (ENV_UNSET);
		env++;
	}
	return (ENV_NOTSET);
}
