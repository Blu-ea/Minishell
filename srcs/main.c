/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/12 18:23:10 by amiguez          ###   ########.fr       */
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
	env = init_env(env);
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
	char			**args;
	long int	ret;

	args = ft_split(line, ' ');
	if (!ft_strncmp(args[0], "echo", 4) && args[0][4] == 0)
		return (bin_echo(args + 1));
	if (!ft_strncmp(args[0], "pwd", 3) && args[0][3] == 0)
		return (bin_pwd());
	// if (!ft_strncmp(args[0], "cd", 2) && args[0][2] == 0)
	// 	return (bin_cd(args + 1));
	if (!ft_strncmp(args[0], "env", 3) && args[0][3] == 0)
		return (bin_env(env));
	if (!ft_strncmp(args[0], "export", 6) && args[0][6] == 0)
	{
		ret = (long int) bin_export(args + 1, env);
		if (ret < 0)
			return (1);
		env = (char **)ret;
		return (0);
	}
	// if (!ft_strncmp(args[0], "unset", 5) && args[0][5] == 0)
	// 	return (bin_unset(args + 1));
	if (!ft_strncmp(args[0], "exit", 4) && args[0][4] == 0)
		return (bin_exit(args + 1));
	return (1);
}

char	**init_env(char **env)
{
	env = ft_tabdup(env);
	return (env);
}
