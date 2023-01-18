/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:16 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/18 18:23:19 by amiguez          ###   ########.fr       */
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

char	*ft_read_line(char **env)
{
	char		*line;
	static char	*history;

	if (!history)
		history = NULL;
	line = readline(PROMT);
	if (line && *line && (ft_strncmp(line, history, ft_strlen(line)) \
			|| ft_strncmp(history, line, ft_strlen(history))))
		add_history(line);
	else if (!line)
		return (NULL);
	if (history)
		free(history);
	history = ft_strdup(line);
	if (g_error_sig)
		env = exp_update (env, "?=1");
	g_error_sig = 0;
	if (!*line)
		return (ft_read_line(env));
	return (line);
}

void	ft_clear_line(void)
{
	clear_history();
	rl_clear_history();
}
