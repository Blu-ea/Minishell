/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/12/26 16:41:56 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ret_exp_update(int *ret);

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
	new_env = *env;
	while (args[i])
	{
		*ret = env_is_set(new_env, args[i]);
		if (*ret == ENV_NOTSET)
			new_env = env_add(new_env, args[i]);
		if (*ret == ENV_SET || *ret == ENV_UNDIFINED)
			new_env = exp_update(new_env, args[i]);
		if (*ret == -1)
			printf("%s export: Something whent wrong\n", PROMT_E);
		if (*ret == -2)
			printf ("%s export: `%s': not a valid identifier\n",
				PROMT_E, args[i]);
		i++;
	}
	ret_exp_update(ret);
	if (new_env == NULL)
		new_env = *env;
	return (new_env);
}

void	ret_exp_update(int *ret)
{
	if (*ret == ENV_NOTSET || *ret == ENV_SET || *ret == ENV_UNDIFINED)
		*ret = 0;
	else if (*ret == -1)
		*ret = 1;
	else
		*ret = 2;
}

int	ft_exp_print(char **env)
{
	int		i;
	char	*temp;
	int		open_colon;

	while (*env)
	{
		if (!ft_strncmp(*env, "_=", 2) || !ft_strncmp(*env, "?", 1))
			env++;
		if (!*env)
			break;
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
		if (open_colon != 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
		env++;
	}
	return (0);
}
