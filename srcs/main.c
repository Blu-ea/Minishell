/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 20:55:28 by amiguez          ###   ########.fr       */
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
		printf("Something went wrong");
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
		// print_command(parse_line);
		if (parse_line && parse_line[0][0])
		{
			ret = execute_pipes(parse_line, &env);
			printf("exit status = %d\n", ret);
			if (errno)
				perror(argv[0]);
			check_fd_leak();
			if (!update_ret(env, ret))
			{
				ret = bin_exit (NULL, env);
				exit(ret); // let it that way ??
			}
		}
		else if (parse_line)
			clear_pipes(parse_line);
		else
			printf("quote error\n");
	}
	printf("env error\n");
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
				printf("%s Something whent wrong\n", PROMT_E);
				return (NULL);
			}
			return (env);
		}
	}
	return (env);
}
