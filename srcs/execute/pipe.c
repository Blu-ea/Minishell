/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:53:35 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/19 15:49:51 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/**
 * @brief Remove the first char of each string in the pipe
 * 
 * @param pipe: The address of the pipe to trim
 */
void	trim_prefix(char **pipe)
{
	int	i;
	int	j;

	i = -1;
	while (pipe[++i])
	{
		j = -1;
		while (pipe[i][++j])
			pipe[i][j] = pipe[i][j + 1];
		pipe[i][j] = 0;
	}
}
