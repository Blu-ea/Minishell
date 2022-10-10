/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/08 10:12:25 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNSET or ENV_SET
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	char	*name_;

	name_ = ft_strjoin(name, "=");
	while (env)
	{
		if (!ft_strncmp(*env, name_, ft_strlen(name_)))
			return (ENV_SET);
		if (!ft_strncmp(*env, name, ft_strlen(name) - 1) && \
				*env[ft_strlen(name)] == 0)
			return (ENV_UNSET);
		env++;
	}
	return (ENV_NOTSET);
}

// char	**env_init(char **env)
// {}
