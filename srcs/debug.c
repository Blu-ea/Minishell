/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 04:00:44 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/18 06:39:27 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	printf ("======debugg   ====\n");
	while (env[i])
	{
		printf ("%s\n", env[i]);
		i++;
	}
	printf ("======debugg   ====\n");
}
