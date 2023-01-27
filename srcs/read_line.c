/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:16 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 10:07:19 by amiguez          ###   ########.fr       */
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

	if (g_error_sig == CHILD)
		env = exp_update (env, "?=130");
	if (g_error_sig == C_BACK)
		env = exp_update (env, "?=131");
	if (g_error_sig == C_C_HEREDOC)
		env = exp_update (env, "?=1");
	g_error_sig = IN_READLINE;
	line = readline(PROMT);
	if (line && *line && (ft_strncmp(line, history, ft_strlen(line)) \
			|| ft_strncmp(history, line, ft_strlen(history))))
		add_history(line);
	else if (!line)
		return (NULL);
	free(history);
	history = ft_strdup(line);
	ft_clear_line(history, NOT_IN_EXIT);
	if (g_error_sig == C_C_CALL)
		env = exp_update (env, "?=1");
	g_error_sig = 0;
	if (!*line)
		return (free(line), ft_read_line(env));
	return (line);
}

void	ft_clear_line(char *new_history, int i)
{
	static char	*history_temp;

	if (i == IN_EXIT)
	{
		free(history_temp);
		clear_history();
		rl_clear_history();
	}
	else
		history_temp = new_history;
}
