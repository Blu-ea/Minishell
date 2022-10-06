/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 05:25:46 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	At initialisation: 
		shlvl+1 ?? shlvl = 0
		pwd='the folder where we are'
		oldpwd -> unset (without an =)
*/

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	init_env(env);
	while (1)
	{
		line = ft_read_line();
	//	Parcing
		built_in(line, env);
		if (line != NULL)
			free(line);
	}
	free(line);
	ft_clear_line();
	return (0);
}

int	built_in(char *line, char **env)
{
	char	**args;

	(void)env;
	(void)line;
	args = ft_split(line, ' ');
	if (!ft_strncmp(args[0], "echo", 4))
		return (bin_echo(args + 1));
	if (!ft_strncmp(args[0], "pwd", 3))
		return (bin_pwd());
	// if (!ft_strncmp(args[0], "exit", 4))
	// 	return (bin_exit(args + 1));
	return (1);
}

void	init_env(char **env)
{
	(void)env;
	// getenv(env)
}
