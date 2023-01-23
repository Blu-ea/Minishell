/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/23 19:39:16 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ret_exp_update(int *ret);
void	export_error(int err, char *arg);

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
		export_error(*ret, args[i]);
		i++;
	}
	ret_exp_update(ret);
	if (new_env == NULL)
		new_env = *env;
	return (new_env);
}

void	export_error(int err, char *arg)
{
	if (err == -1 || err == -2)
		write (2, PROMT_E, ft_strlen(PROMT_E));
	if (err == -1)
		write (2, ": export: Something went wrong\n", 32);
	if (err == -2)
	{
		write (2, ": export: `", 11);
		write (2, arg, ft_strlen(arg));
		write (2, "': not a valid identifier\n", 27);
	}
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
