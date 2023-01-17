/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:52 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/17 16:43:34 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a recreation of the export function in bash

void	sorttab(char **test);
int		cmp_export(char *str1, char *str2);
int		ft_exp_print(char **env, int i);

void	print_t_export(char **env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = malloc(sizeof(char *) * (ft_tablen(env) + 1));
	if (!temp)
		return ;
	temp[ft_tablen(env)] = NULL;
	while (i < ft_tablen(env))
	{
		temp[i] = env[i];
		i++;
	}
	sorttab(temp);
	ft_exp_print(temp, -1);
	free(temp);
}

void	sorttab(char **test)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (test[i])
	{
		j = i + 1;
		while (test[j])
		{
			if (cmp_export(test[i], test[j]) > 0)
			{
				temp = test[i];
				test[i] = test[j];
				test[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	cmp_export(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && \
			str1[i] == str2[i] && \
			str1[i] != '=' && str2[i] != '=')
		i++;
	if (str1[i] == '=' && str2[i] == '=')
		return (0);
	if (str2[i] == '=')
		return (1);
	if (str1[i] == '=')
		return (-1);
	return (str1[i] - str2[i]);
}

int	ft_exp_print(char **env, int i)
{
	char	*temp;
	int		open_colon;

	while (*env)
	{
		open_colon = 0;
		i = -1;
		if (!ft_strncmp(*env, "_=", 2) || !ft_strncmp(*env, "?", 1))
			env++;
		if (!*env)
			break ;
		temp = *env;
		write(1, "declare -x ", 11);
		while (temp[++i])
		{
			write(1, &temp[i], 1);
			if (temp[i] == '=' && open_colon == 0)
				open_colon = write(1, "\"", 1);
		}
		if (open_colon != 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
		env++;
	}
	return (0);
}
