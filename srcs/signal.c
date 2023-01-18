/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:00:51 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/18 17:23:43 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	rl_redisplay();
	ft_putstr_fd("  \b\b", 2);
	rl_on_new_line();
	ft_putchar_fd('\n', 2);
	rl_replace_line("", 0);
	rl_redisplay();
	g_error_sig = 1;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 2);
}
