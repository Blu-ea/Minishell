/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:00:51 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/24 19:41:48 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_error_sig == IN_HEREDOC)
		exit(1);
	if (g_error_sig == CHILD)
		return ;
	if (g_error_sig == IN_READLINE || g_error_sig == C_C_CALL)
	{
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_sig = C_C_CALL;
	}
	else
	{
		rl_replace_line("", 0);
		ft_putstr_fd("  \b\b", 2);
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_error_sig == IN_HEREDOC)
	{
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		return ;
	}
	if (g_error_sig == LAUNCHED_HEREDOC)
		return ;
	if (g_error_sig == IN_READLINE)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
	}
	else
	{
		rl_on_new_line();
		ft_putstr_fd("\b\b  \b\b", 2);
	}
}

void	sigint_inpipe(int sig)
{
	(void)sig;
	return ;
}
