/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:51:54 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/15 18:20:09 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cannot unset _
*/

void	free_unset(char **env);

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
		if (set == -1)
			printf("%s export: Something whent wrong\n", PROMT_E);
		if (set == -2)
			printf ("%s export: `%s': not a valid identifier\n",
				PROMT_E, args[i]);
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