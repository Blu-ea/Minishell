/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/18 19:28:53 by jcollon          ###   ########lyon.fr   */
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
		printf("Something when wrong");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (env)
	{
		ret = 1;
		// i = -1;
		line = ft_read_line(env);
		if (line == NULL)
			bin_exit(NULL);
		parse_line = parse(line, env);
		// print_command(parse_line);
		ret = execute_pipes(parse_line, env);
		printf("exit status = %d\n", ret);
		if (errno)
			perror(argv[0]);
		check_fd_leak();
		// while (parse_line && parse_line[++i])
		// 	ret = built_in(parse_line[i], &env);
		if (ret != -1 && !update_ret(env, ret))
			bin_exit (NULL);
		if (line != NULL)
			free(line);
		// i = -1;
		// free(parse_line);
	}
	return (1);
}

int	built_in(char **args, char ***env)
{
	int		ret;
	int		i;

	ret = 1;
	printf("args[0] = %s\n", args[0]);
	printf("==========\n");
	if (!ft_strncmp(args[0], "0echo", 5) && args[0][5] == 0)
		ret = bin_echo(args + 1);
	if (!ft_strncmp(args[0], "0pwd", 4) && args[0][4] == 0)
		ret = bin_pwd();
	if (!ft_strncmp(args[0], "0cd", 3) && args[0][3] == 0)
		ret = bin_cd(args + 1, *env);
	if (!ft_strncmp(args[0], "0env", 4) && args[0][4] == 0)
		ret = bin_env(*env);
	if (!ft_strncmp(args[0], "0export", 7) && args[0][7] == 0)
		*env = bin_export(args + 1, env, &ret);
	if (!ft_strncmp(args[0], "0unset", 6) && args[0][6] == 0)
		ret = bin_unset(args + 1, env);
	if (!ft_strncmp(args[0], "0exit", 5) && args[0][5] == 0)
		ret = bin_exit(args + 1);
	printf("==========\n");
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	return (ret);
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
