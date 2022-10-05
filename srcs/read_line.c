/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:16 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/03 18:56:40 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	// readline
	// rl_clear_history
	rl_on_new_line
	rl_replace_line
	rl_redisplay
	add_history
*/

#include "minishell.h"

char	*ft_read_line(void)
{
	char	*line;

	line = readline(PROMT);
	if (line && *line)
		add_history(line);
	else if (!line)
		return (NULL);
	return (line);
}

void	ft_clear_line(void)
{
	// rl_clear_history();
}
