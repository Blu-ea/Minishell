/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:43:04 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/26 19:59:41 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_env_mod(int pwd[2], char **env, char *new_path, char *old_path);

int	cd_update_env(char *new_path, char *old_path, char **env)
{
	int		pwd[2];
	int		i;

	pwd[0] = -1;
	pwd[1] = -1;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4) || !ft_strncmp(env[i], "PWD", 4))
			pwd[1] = i;
		if (!ft_strncmp(env[i], "OLDPWD", 7) \
				|| !ft_strncmp(env[i], "OLDPWD=", 7))
			pwd[0] = i;
	}
	i = cd_env_mod(pwd, env, new_path, old_path);
	free(new_path);
	if (i == 1)
		free(env[pwd[1]]);
	else if (i == 2)
		free(env[pwd[0]]);
	if (i != 0)
		cd_error(MALLOC_ERROR, "cd");
	if (i != 0)
		return (1);
	return (0);
}

int	cd_env_mod(int pwd[2], char **env, char *new_path, char *old_path)
{
	int	i;

	i = 0;
	if (pwd[0] != -1)
	{
		free(env[pwd[0]]);
		if (pwd[1] != -1 && !ft_strncmp(env[pwd[1]], "PWD=", 4))
			env[pwd[0]] = ft_strjoin("OLDPWD=", env[pwd[1]] + 4);
		else if (pwd[1] != -1 && !ft_strncmp(env[pwd[1]], "PWD", 4))
			env[pwd[0]] = ft_strdup("OLDPWD");
		else
			env[pwd[0]] = ft_strjoin("OLDPWD=", old_path);
		if (env[pwd[0]] == NULL)
			i++;
	}
	if (pwd[1] != -1)
	{
		free(env[pwd[1]]);
		env[pwd[1]] = ft_strjoin("PWD=", new_path);
		if (env[pwd[1]] == NULL)
			i += 2;
	}
	return (i);
}
