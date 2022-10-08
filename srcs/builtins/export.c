/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:41:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/08 07:28:23 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	ft_exp_print(char **env);

int	bin_export(char **args, char **env)
{
	// int		i;
	// char	**new_env;

	if (*args == NULL)
		return (ft_exp_print(env));
	// while (*args)
	return (0);
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
