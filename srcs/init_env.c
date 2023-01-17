/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:27:19 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/15 23:09:38 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Need to Modif all return there so that there isn t any leaks
*/

char	**init_shlvl(char **env);
char	**init_oldpwd(char **env);
char	**init_pwd(char **env);
char	**init_failed(char **env, char *temp);

char	**init_env(char **env)
{
	env = ft_tabdup(env);
	env = env_add(env, "?=0");
	if (!env)
		return (NULL);
	env = init_shlvl(env);
	env = init_oldpwd(env);
	env = init_pwd(env);
	return (env);
}

char	**init_pwd(char **env)
{
	char	*temp;
	int		i;

	i = env_is_set(env, "PWD");
	if (i == -1)
		return (NULL);
	temp = ft_strjoin_free("PWD=", getcwd(NULL, 0), FREE_S2);
	if (!temp)
		return (NULL);
	if (i == ENV_NOTSET)
		env = env_add(env, temp);
	if (i == ENV_SET || i == ENV_UNDIFINED)
		env = exp_update(env, temp);
	free(temp);
	return (env);
}

char	**init_oldpwd(char **env)
{
	char	*temp;
	int		i;

	i = env_is_set(env, "OLDPWD");
	if (i == -1)
		return (init_failed(env, NULL));
	if (i == ENV_NOTSET)
		return (env_add(env, "OLDPWD"));
	temp = env_get_value(env, "OLDPWD");
	if (!temp)
		return (init_failed(env, temp));
	if (access(temp, F_OK))
		env = unset_del(env, "OLDPWD");
	free(temp);
	return (env);
}

char	**init_shlvl(char **env)
{
	char	*temp;
	int		i;

	i = env_is_set(env, "SHLVL");
	if (i == -1)
		return (init_failed(env, NULL));
	if (i == ENV_NOTSET)
		return (env_add(env, "SHLVL=1"));
	if (i == ENV_UNDIFINED)
		return (exp_update(env, "SHLVL=1"));
	temp = env_get_value(env, "SHLVL");
	if (!temp)
		return (init_failed(env, NULL));
	i = ft_atoi(temp);
	free(temp);
	temp = ft_itoa(i + 1);
	if (!temp)
		return (init_failed(env, NULL));
	temp = ft_strjoin_free("SHLVL=", temp, FREE_S2);
	if (!temp)
		return (init_failed(env, NULL));
	env = exp_update(env, temp);
	free(temp);
	return (env);
}

char	**init_failed(char **env, char *temp)
{
	int	i;

	i = -1;
	if (temp)
		free(temp);
	while (env[++i])
		free(env[i]);
	free(env);
	return (NULL);
}
