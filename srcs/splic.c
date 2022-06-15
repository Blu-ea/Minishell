/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:12:49 by jcollon           #+#    #+#             */
/*   Updated: 2022/06/15 06:30:06 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ft_split('|')
 * 
 * @param line 
 * @return char** 
 */
char	**split_pipe(char *line)
{
	return (ft_split(line, '|'));
}

/**
 * @brief ft_split(' ')
 * 
 * @param line 
 * @return char** 
 */
char	**split_cmd(char *line)
{
	return (ft_split(line, ' '));
}
