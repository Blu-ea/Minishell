/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:51:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/26 18:38:11 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cannot unset _
*/

char	**unset_del(char ***env, char *arg);

int	bin_unset(char **args, char ***env)
{
	int		i;
	int		set;

	i = -1;
	if (!*args)
		return (0);
	while (args[++i])
	{
		set = env_is_set(*env, args[i]);
		if (set == ENV_SET || set == ENV_UNSET)
			*env = unset_del(env, args[i]);
		if (set == -1)
			printf("%s export: Something whent wrong\n", PROMT_E);
	}
	return (0);
}

char	**unset_del(char ***env, char *arg)
{
	int		i;
	char	**new_env;

	i = ft_tablen(*env);
	new_env = malloc(sizeof(char *) * i--);
	if (!new_env)
		return (*env);
	new_env[i] = 0;
	i = 0;
	printf("here\n");
	while (ft_strncmp(*env[i], arg, ft_strlen(arg)) && \
		*env[i][ft_strlen(arg)] != '=' && *env[i])
	{
		new_env[i] = *env[i];
		i++;
		printf("while\n");
	}	
	printf("there\n");
	printf("i = %d\n", i);
	while (*env[++i + 1])
		new_env[i] = *env[i + 1];
	printf("nope pls\n");
	free(*env);
	return (new_env);
}
