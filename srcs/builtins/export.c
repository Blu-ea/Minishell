/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/08 10:15:18 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_error(char **new_env, int i);
char	**env_add(char **env, char *args);
char	**env_update(char **env, char *args);
int		ft_exp_print(char **env);


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
*/

char	**bin_export(char **args, char **env)
{
	int		i;
	char	**new_env;

	//split with '=' to get name
	//look if correct name 
	i = env_is_set();
	new_env = NULL;
	if (i == ENV_NOTSET)
		new_env = env_add(env, args);
	else
		new_env = env_update(env, args);
	return (new_env);
}

int	ft_exp_print(char **env)
{
	int		i;
	char	*temp;

	while (*env)
	{
		i = 0;
		temp = *env;
		write(1, "declare -x ", 11);
		while (temp[i])
		{
			write(1, &temp[i], 1);
			if (temp[i] == '=')
				write(1, "\"", 1);
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
}

int	env_error(char **new_env, int i)
{
	while (i--)
		free(new_env[i]);
	free(new_env);
	return (EXIT_FAILURE);
}
