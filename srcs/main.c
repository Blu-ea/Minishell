/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 23:30:41 by jcollon          ###   ########lyon.fr   */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		ret;
	char	***parse_line;

	(void)argc;
	(void)argv;
	env = init_env(env);
	if (env == NULL)
		ft_print_error("Something went wrong");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (env)
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
		if (parse_line && parse_line != (char ***)1 && parse_line[0][0])
		{
			ret = execute_pipes(parse_line, &env);
			if (errno)
				perror(argv[0]);
			if (!update_ret(env, ret))
			{
				ret = bin_exit (NULL, env);
				exit(ret); // let it that way ??
			}
		}
		else if (parse_line && parse_line != (char ***)1)
			clear_pipes(parse_line);
		else
			ft_print_error("Quote error");
	}
	ft_print_error("env error");
	return (1);
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
	ft_putstr_fd(" ", 2);
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
	ft_putstr_fd(PROMT_E, 2);
	ft_putstr_fd(" ", 2);
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
