/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:07:09 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/23 19:40:27 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	/!\ Do Nothing if on a pipe /!\

	don t exit if arg[0] ->int && more that 1 arg

	exit if arg[0] -> char*  $? 255
	exit if none arg		$? 0
	print "exit" if exit
*/

int	post_exit(char **env, int ret);
int	exit_alpha(char *temp, char **arg, int pipe);

/**
 * @brief Will 
 * 
 * @param arg: exit code
 * @param env: enviroment 
 * @return beteewn 0 and 255 if need to exit -1 if not || env is free if need
 * to exit
 */
int	bin_exit(char **arg, char **env)
{
	char	*temp;

	if (arg == NULL || !*arg)
	{
		write(2, "exit\n", 6);
		ft_clear_line(NULL, IN_EXIT);
		return (post_exit(env, 0));
	}
	temp = ft_itoa(ft_atoi(*arg));
	if (ft_strncmp(temp, arg[0], ft_strlen(arg[0])) != 0)
		return (post_exit(env, exit_alpha(temp, arg, NOT_IN_PIPE)));
	free(temp);
	temp = *arg;
	while (*arg)
		arg++;
	arg--;
	if (temp - *arg != 1 && temp - *arg != 0)
	{
		ft_print_error2("exit", "too many arguments");
		return (-1);
	}
	write(2, "exit\n", 6);
	ft_clear_line(NULL, IN_EXIT);
	return (post_exit(env, ft_atoi(temp) % 256));
}

int	exit_alpha(char *temp, char **arg, int pipe)
{
	free(temp);
	write (2, PROMT_E, ft_strlen(PROMT_E));
	write (2, ": exit: ", 8);
	write (2, *arg, ft_strlen(*arg));
	write (2, ": Numeric argument required\nexit\n", 34);
	if (pipe != IN_PIPE)
		ft_clear_line(NULL, IN_EXIT);
	return (2);
}

int	post_exit(char **env, int ret)
{
	int	i;

	i = -1;
	while (env[++i])
		free (env[i]);
	free (env);
	return (ret);
}
