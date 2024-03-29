/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:07:09 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 14:18:13 by amiguez          ###   ########.fr       */
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

int	post_exit(char **env, int ret, int arg);
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
		return (post_exit(env, -1, NO_ARGS));
	}
	temp = ft_itoa(ft_atoi(*arg));
	if (ft_strncmp(temp, arg[0], ft_strlen(arg[0])) != 0)
		return (post_exit(env, exit_alpha(temp, arg, NOT_IN_PIPE), ARGS));
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
	return (post_exit(env, ft_atoi(*arg), ARGS));
}

int	exit_alpha(char *temp, char **arg, int pipe)
{
	free(temp);
	write (2, PROMT_E, ft_strlen(PROMT_E));
	write (2, ": exit: ", 8);
	write (2, *arg, ft_strlen(*arg));
	write (2, ": numeric argument required\n", 30);
	if (pipe != IN_PIPE)
	{
		write(2, "exit\n", 5);
		ft_clear_line(NULL, IN_EXIT);
	}
	return (255);
}

int	post_exit(char **env, int ret, int arg)
{
	int		i;
	char	*temp;

	if (arg == NO_ARGS)
	{
		temp = env_get_value(env, "?");
		ret = ft_atoi(temp);
		if (temp)
			free(temp);
	}
	i = -1;
	if (env)
	{
		while (env[++i])
			free (env[i]);
		free (env);
	}
	while (ret <= 0)
		ret += 256;
	return (ret);
}
