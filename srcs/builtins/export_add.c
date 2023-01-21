/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:14:35 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 22:13:59 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_error(char **new_env, int i);
char	*ft_remove_plus(char *args);
char	**freeall(char **env, char *temp, char **new_env, int i);

char	**env_add(char **env, char *args)
{
	int		i;
	char	**new_env;
	char	*temp;

	if (!env)
		return (NULL);
	temp = ft_remove_plus(args);
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	new_env[i + 1] = NULL;
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (env_error(new_env, i));
	}
	new_env[i] = ft_strdup(temp);
	if (!new_env[i])
		return (env_error(new_env, i));
	return (freeall(env, temp, new_env, i));
}

char	**freeall(char **env, char *temp, char **new_env, int i)
{
	while (i--)
		free(env[i]);
	free(env);
	free(temp);
	return (new_env);
}

char	**env_error(char **new_env, int i)
{
	write (2, PROMT_E, ft_strlen(PROMT_E));
	write (2, "Something went wrong", 21);
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (NULL);
}

char	*ft_remove_plus(char *args)
{
	int		i;
	int		j;
	char	*new_args;

	i = 0;
	while (args[i] && args[i] != '=' && args[i] != '+')
		i++;
	if (args[i] == '=' || !args[i])
		return (ft_strdup(args));
	new_args = malloc(sizeof(char) * ft_strlen(args));
	if (!new_args)
		return (NULL);
	new_args[ft_strlen(args)-1] = '\0';
	i = -1;
	while (args[++i] != '+')
		new_args[i] = args[i];
	i--;
	j = i + 1;
	while (new_args[++i] && args[++j])
		new_args[i] = args[j];
	return (new_args);
}
