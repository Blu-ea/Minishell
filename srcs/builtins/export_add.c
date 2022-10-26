/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:14:35 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/26 16:21:01 by amiguez          ###   ########.fr       */
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

	temp = ft_remove_plus(args);
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
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
	new_env[i + 1] = NULL;
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

// char	**env_add(char **env, char *temp)
// { // Need to remove the + if present
// 	char	**new_env;
// 	int		i;

// 	i = -1;
// 	new_env = malloc(sizeof(char *) * ft_tablen(env) + 2);
// 	if (!new_env)
// 		return (NULL);
// 	while (env[++i])
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		printf("malloc %p\n", new_env[i]);
// 	}
// 	new_env[i] = ft_strdup(args);
// 	if (!new_env[i])
// 		return (env_error(new_env, i));
// 	new_env[i + 1] = 0;
// 	while (i--)
// 	{
// 		printf("freeing %p\n", env[i]);
// 		free(env[i]);
// 	}
// 	free(env);
// 	return (new_env);
// }

char	**env_error(char **new_env, int i)
{
	printf("ERROR === env_error \n");
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (NULL);
}

char	*ft_remove_plus(char *args)
{
	int		i;
	char	*new_args;

	i = 0;
	while (args[i] && (args[i] != '=' && args[i] != '+'))
		i++;
	if (args[i] == '=' || !args[i])
		return (ft_strdup(args));
	new_args = malloc(sizeof(char) * ft_strlen(args));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args[i] != '+')
	{
		new_args[i] = args[i];
		i++;
	}
	while (args[i])
	{
		new_args[i] = args[i + 1];
		i++;
	}
	new_args[i] = '\0';
	return (new_args);
}
