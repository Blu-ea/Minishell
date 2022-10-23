/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 06:59:56 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/23 12:31:24 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**yes_append(char **env, char *args, int i, char *temp);
char	**no_append(char **env, char *args, int i);
/*
char	**split_egual(char *args);

char	**env_update(char **env, char *args)
{
	int		i;
	char	**temp;
	int		len;

	i = 0;
	temp = split_egual(args);
	if (temp == NULL)
		return (env);
	printf ("temp[0] = %s, temp[1] = %s\n", temp[0], temp[1]);
	if (temp[1] == 0)
		return (NULL);
	len = ft_strlen(temp[0]);
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp[0], len) && \
				(env[i][len] == '=' || env[i][len] == 0))
			break ;
		i++;
	}
	free(env[i]);
	env[i] = ft_strdup(args);
	return (env);
}

char	**split_egual(char *args)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * 3);
	if (!ret)
		return (NULL);
	ret[2] = 0;
	i = 0;
	while (args[i] && !(args[i] == '+' || args[i] == '='))
		i++;
	//verif for last char (= or +)
	// diff return if +
	if (args[i] == 0)
		return (NULL);
	ret[0] = malloc(sizeof(char) * (i + 1));
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	ret[0][i] = 0;
	while (--i + 1)
		ret[0][i] = args[i];
	i = ft_strlen(ret[0]) + 2;
	while (args[i])
		i++;
	ret[1] = malloc(sizeof(char) * i - ft_strlen(ret[0]) - 1);
	if (!ret[i])
	{
		free(ret[0]);
		free(ret);
		return (NULL);
	}
	while (i - (ft_strlen(ret[0])) + 1)
	{
		ret[1][i - (ft_strlen(ret[0]))] = args[i];
		i--;
	}
	return (ret);
}*/

// make a fonction that fetch the name with the egale at the end 
// 			take a *int for append mode
// 	return env if no egale
// search for the name in the env (strncmp (ret, env[i],strlen(ret)) == 0)
// look at append mode
// if append mode == 0, free env[i] and replace it with the new value
// if append mode == 1, free env[i] and replace it with the old value + new value

char	**env_update(char **env, char *args)
{
	int		i;
	char	*temp;
	int		len;
	int		append;

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
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, len) && \
				(env[i][len] == '=' || env[i][len] == 0))
			break;
		i++;
	}
	if (append == 0)
	{
		return (no_append(env, args, i));
		free(temp);
	}
	return (yes_append(env, args, i, temp));
}

char	**no_append(char **env, char *args, int i)
{
	printf("env = %p\n", env);
	printf("env[%d] = %s\n", i-1, env[i-1]);
	free(env[i]);
	env[i] = ft_strdup(args);
	return (env);
}

char	**yes_append(char **env, char *args, int i,char *name)
{
	char	*temp;
	char	*temp2;

	printf("check append\n");
	temp = ft_strchr(env[i], '=');
	printf("temp = %s\n", temp);
	temp2 = ft_strjoin(temp + 1, &args[ft_strlen(name) + 2]);
	printf("temp2 = %s\n", temp2);
	free(env[i]);
	temp = ft_strjoin(name, "=");
	free(name);
	env[i] = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (env);
}
