/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:51:28 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/11 18:23:11 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrurn ENV_NOTSET, ENV_UNSET or ENV_SET 
 * 	Return -1 if the name is not valuale Not implemented yet
 * 
 * @param env 
 * @param name 
 */
int	env_is_set(char **env, char *name)
{
	char	*name_;
	int		i;

	i = 0;
	name_ = ft_strjoin(name, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], name_, ft_strlen(name_)))
			return (ENV_SET);
		if (!ft_strncmp(env[i], name, ft_strlen(name) - 1) && \
				env[i][ft_strlen(name)] == 0)
			return (ENV_UNSET);
		i++;
	}
	free(name_);
	return (ENV_NOTSET);
}

// char	**env_init(char **env)
// {}
