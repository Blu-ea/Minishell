/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:59:00 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/16 21:54:28 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Print env if no arg 
	Dont show variable without an = signe 
*/

int	bin_env(char **env)
{
	int	i;
	int	print;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		print = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=' && env[i][0]!= '?')
				print = 1;
			j++;
		}
		if (print == 1)
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
