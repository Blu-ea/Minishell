/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:44:49 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 02:20:14 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_flag(char *arg);
void	print_tab(char **env);

/*
	look for any '-n' with any number of 'n'
	can be multiple numbers of '-n' one after the other
	only 1 '-'
*/

int	bin_echo(char **args)
{
	int	flag;

	flag = 0;
	while (is_flag(*args) == 0)
	{
		flag = 1;
		args++;
	}
	while (*args)
	{
		printf("%s",*args);
		args++;
		if (*args)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

int	is_flag(char *arg)
{
	int	i;
	int	flag;

	if (!arg)
		return (1);
	i = 2;
	flag = -1;
	if (ft_strlen(arg) >= 2)
		flag = ft_strncmp(arg, "-n", 2);
	while (flag == 0 && arg[i])
	{
		if (arg[i] != 'n')
			flag = -1;
		i++;
	}
	return (flag);
}
