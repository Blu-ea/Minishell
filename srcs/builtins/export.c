/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/11 18:20:36 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_error(char **new_env, int i);
char	**env_add(char **env, char *args);
char	**env_update(char **env, char *args);


/*
	If no args, show every variable in env (even non set one)
	Do not show _
	set 

	for the name of the input :
		Only numbers and letters and _
		1st is a letter and _
	
	if set and no desc given
		Dont update

	Can not update "_"

	if expot PATH+="qqc" add "qqc" at the end of $PATH
	/!\ Do not work fot PATH=+qqc -> will update $PATH to "+qqc" /!\
*/

char	**bin_export(char **args, char **env)
{
	int		i;
	char	**new_env;

	new_env = NULL;
	i = 0;
	if (!*args)
		print_t_export(env);
	while (args[i])
	{
		printf("%d", env_is_set(env, args[i]));
		if (env_is_set(env, args[i]) == ENV_NOTSET)
			printf("yep ca marche pas\n");
			// new_env = env_add(env, args[i]);
		else
			printf("Nope ca update\n");
	// 		new_env = env_update(env, args[i]);
		i++;
	}
	return (new_env);
}

int	ft_exp_print(char **env)
{
	int		i;
	char	*temp;
	int		open_colon;

	while (*env)
	{
		open_colon = 0;
		i = 0;
		temp = *env;
		write(1, "declare -x ", 11);
		while (temp[i])
		{
			write(1, &temp[i], 1);
			if (temp[i] == '=' && open_colon == 0)
				open_colon = write(1, "\"", 1);
			i++;
		}
		write(1, "\"", 1);
		write(1, "\n", 1);
		env++;
		if (!ft_strncmp(*env, "_=", 2))
			env++;
	}
	return (0);
}

char	**env_update(char **env, char *args)
{
	(void)env;
	(void)args;
	return (NULL);
}

char	**env_add(char **env, char *args)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = malloc(sizeof(char *) * ft_tablen(env) + 2);
	if (!new_env)
		return (NULL);
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			env_error(new_env, i);
	}
	new_env[ft_tablen(env) + 1] = ft_strdup(args);
	if (new_env[i])
		env_error(new_env, i);
	new_env[ft_tablen(env) + 2] = 0;
	printf("test\njesusisla\n");
	return (new_env);
}

int	env_error(char **new_env, int i)
{
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (EXIT_FAILURE);
}
