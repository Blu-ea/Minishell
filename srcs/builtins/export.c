/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/18 23:13:02 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_error(char **new_env, int i);
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

char	**bin_export(char **args, char ***env, int *ret)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!*args)
		print_t_export(*env);
	while (args[i])
	{
		new_env = NULL;
		*ret = env_is_set(*env, args[i]);
		if (*ret == ENV_NOTSET){
			printf("ca add\n");
			new_env = env_add(*env, args[i]);}
		if (*ret == ENV_SET || *ret == ENV_UNSET)
			printf("Nope ca update\n");
			// new_env = env_update(env, args[i]);
		if (*ret == -1)
			printf("%s export: Something whent wrong\n", PROMT_E); 
		if (*ret == -2)
			printf ("%s export: `%s': not a valid identifier\n",
				PROMT_E, args[i]);
		i++;
		if (new_env == NULL)
			*env = new_env;
	}
	// free(env);
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
		printf("%p - > %s\n", temp, temp);
		write(1, "declare -x ", 11);
		while (temp[i])
		{
			write(1, &temp[i], 1);
			if (temp[i] == '=' && open_colon == 0)
				open_colon = write(1, "\"", 1);
			i++;
		}
		if (open_colon != 0)
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
		new_env[i] = env[i];
		// new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(args);
	// printf ("new == %s\n", new_env[i]);
	// printf ("new == %p\n", new_env[i]);
	if (!new_env[i])
		return (env_error(new_env, i));
	new_env[i + 1] = 0;
	// while (i--)
	// 	free(env[i]);
	// free(env);
	return (new_env);
}

char	**env_error(char **new_env, int i)
{
	while (i--)
		free(new_env[i]);
	free(new_env);
	printf("ERROR === env_error \n");
	return (NULL);
}
