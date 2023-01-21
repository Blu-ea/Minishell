/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:51:54 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 22:14:04 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cannot unset _
*/

void	free_unset(char **env);
void	unset_error(int err, char *arg);

int	bin_unset(char **args, char ***env)
{
	int	i;
	int	set;
	int	ret;

	ret = 0;
	i = -1;
	if (!*args)
		return (ret);
	while (args[++i])
	{
		set = env_is_set(*env, args[i]);
		if (set == ENV_SET || set == ENV_UNDIFINED)
			*env = unset_del(*env, args[i]);
		unset_error(set, args[i]);
		if (set < 0)
			ret = 1;
	}
	return (ret);
}

char	**unset_del(char **env, char *arg)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(env)));
	if (!new_env)
		return (NULL);
	while ((env)[++i])
	{
		if (ft_strncmp((env)[i], arg, ft_strlen(arg)) != 0)
			new_env[j++] = ft_strdup((env)[i]);
	}
	new_env[j] = NULL;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

void	free_unset(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	unset_error(int err, char *arg)
{
	if (err == -1 || err == -2)
		write (2, PROMT_E, ft_strlen(PROMT_E));
	if (err == -1)
		write (2, " export: Something went wrong\n", 32);
	if (err == -2)
	{
		write (2, " export: `", 11);
		write (2, arg, ft_strlen(arg));
		write (2, "': not a valid identifier\n", 27);
	}
}
