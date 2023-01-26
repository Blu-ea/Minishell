/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 00:12:22 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
/*
	At initialisation: 
		shlvl+1 ?? shlvl = 0
		pwd='the folder where we are'
		oldpwd -> unset (without an =)
*/

char	**update_ret(char **env, int ret);
char	**loop(char **env, int ret, char *line, char ***parse_line);

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	env = init_env(env);
	if (env == NULL)
		ft_print_error("Something went wrong");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (env)
	{
		env = loop(env, 0, NULL, NULL);
	}
	ft_print_error("env error");
	return (1);
}

char	**loop(char **env, int ret, char *line, char ***parse_line)
{
	ret = 1;
	line = ft_read_line(env);
	if (line == NULL)
	{
		ret = bin_exit(NULL, env);
		exit(ret);
	}
	parse_line = parse(line, env);
	free(line);
	if (!parse_line)
		ret = 2;
	else
		ret = execute_pipes(parse_line, &env);
	if (errno && errno != 4)
		perror(PROMT_E);
	if (!update_ret(env, ret))
	{
		ret = bin_exit (NULL, env);
		exit(ret);
	}
	return (env);
}

char	**update_ret(char **env, int ret)
{
	int		i;
	char	*temp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "?", 1))
		{
			free(env[i]);
			temp = ft_itoa(ret);
			env[i] = ft_strjoin("?=", temp);
			free(temp);
			if (env[i] == NULL)
			{
				ft_free_2d_array(env);
				ft_print_error("Something went wrong");
				return (NULL);
			}
			return (env);
		}
	}
	return (env);
}

void	ft_print_error(char *str)
{
	ft_putstr_fd(PROMT_E, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	if (errno)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
}

void	ft_print_error2(char *str, char *str2)
{
	if (!str)
	{
		ft_print_error(str2);
		return ;
	}
	ft_putstr_fd(PROMT_E, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	if (errno)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
}
