/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:52 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/11 18:21:59 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a recreation of the export function in bash

void	sorttab(char **test);
int		cmp_export(char *str1, char *str2);

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
	ft_exp_print(temp);
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
