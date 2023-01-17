/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 06:59:56 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/15 17:52:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**yes_append(char **env, char *args, int i, char *temp);
char	**no_append(char **env, char *args, int i, char *temp);

// make a fonction that fetch the name with the egale at the end 
// 			take a *int for append mode
// 	return env if no egale
// search for the name in the env (strncmp (ret, env[i],strlen(ret)) == 0)
// look at append mode
// if append mode == 0, free env[i] and replace it with the new value
// if append mode == 1, free env[i] and replace it with the old value+new value

char	**exp_update(char **env, char *args)
{
	int		i;
	char	*temp;
	int		len;
	int		append;

	if (!env)
		return (NULL);
	i = 0;
	append = 0;
	temp = ft_search(args, '=');
	if (temp == NULL)
		return (env);
	if (temp[ft_strlen(temp) - 1] == '+')
	{
		append = 1;
		temp[ft_strlen(temp) - 1] = 0;
	}
	len = ft_strlen(temp);
	while (env[i] && !(!ft_strncmp(env[i], temp, len) && \
				(env[i][len] == '=' || env[i][len] == 0)))
		i++;
	if (append == 0)
		return (no_append(env, args, i, temp));
	return (yes_append(env, args, i, temp));
}

char	**no_append(char **env, char *args, int i, char *temp)
{
	free(env[i]);
	env[i] = ft_strdup(args);
	free(temp);
	return (env);
}

char	**yes_append(char **env, char *args, int i, char *name)
{
	char	*temp;
	char	*temp2;

	temp = ft_strchr(env[i], '=');
	if (temp == 0)
		temp2 = ft_strdup(&args[ft_strlen(name) + 2]);
	else
		temp2 = ft_strjoin(temp + 1, &args[ft_strlen(name) + 2]);
	free(env[i]);
	temp = ft_strjoin(name, "=");
	free(name);
	env[i] = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (env);
}
