/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 06:59:56 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/19 07:41:53 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_egual(char *args);

char	**env_update(char **env, char *args)
{
	int		i;
	char	**temp;
	int		len;

	i = 0;
	temp = split_egual(args);
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
	while (args[i] && args[i] != '+')
		i++;
	ret[0] = malloc(sizeof(char) * (i));
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	ret[0][--i] = 0;
	while (i--)
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
	while (i - (ft_strlen(ret[0])))
	{
		ret[1][i - (ft_strlen(ret[0]))] = args[i];
		i--;
	}
	return (ret);
}
