/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/12/26 16:31:25 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	(void)argc;
	(void)argv;
	env = init_env(env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		line = ft_read_line();
		if (line == NULL)
			bin_exit(NULL);
	//	Parcing
		printf ("Pars : '%s'\n",mini_parsing(line, env));
		ret = built_in(line, &env);
		if (!update_ret(env, ret))
			bin_exit (NULL);
		if (line != NULL)
			free(line);
	}
	return (0);
}

int	built_in(char *line, char ***env)
{
	char	**args;
	int		ret;
	int		i;

	ret = 1;
	args = ft_split(line, ' ');
	if (!ft_strncmp(args[0], "echo", 4) && args[0][4] == 0)
		ret = bin_echo(args + 1);
	if (!ft_strncmp(args[0], "pwd", 3) && args[0][3] == 0)
		ret = bin_pwd();
	if (!ft_strncmp(args[0], "cd", 2) && args[0][2] == 0)
		ret = bin_cd(args + 1, *env);
	if (!ft_strncmp(args[0], "env", 3) && args[0][3] == 0)
		ret = bin_env(*env);
	if (!ft_strncmp(args[0], "export", 6) && args[0][6] == 0)
		*env = bin_export(args + 1, env, &ret);
	if (!ft_strncmp(args[0], "unset", 5) && args[0][5] == 0)
		ret = bin_unset(args + 1, env);
	if (!ft_strncmp(args[0], "exit", 4) && args[0][4] == 0)
		ret = bin_exit(args + 1);
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	return (ret);
}

char	**init_env(char **env)
{
	int	i;
	// int	j;

	env = ft_tabdup(env);
	env = env_add(env, "?");
	if (!env)
		return (NULL);
	i = env_is_set(env, "SHLVL");
	if (i == ENV_NOTSET)
		env_add(env, "SHLVL=1");
	// if (env_get_value)
	// j = -1;
	// while (env[++j])

	
	// ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1));
	return (env);
}

char	**update_ret(char **env, int ret)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "?", 1))
		{
			free(env[i]);
			env[i] = ft_strjoin("?", ft_itoa(ret));
			if (env[i] == NULL)
			{
				ft_free_2d_array(env);
				printf("%s Something whent wrong\n", PROMT_E);
				return (NULL);
			}
			return (env);
		}
		i++;
	}
	return (env);
}
