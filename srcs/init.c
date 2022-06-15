/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 05:38:29 by jcollon           #+#    #+#             */
/*   Updated: 2022/06/15 06:12:12 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief initialise the shell (set shlvl+1)
 * \TODO init shell struct
 * 
 * @param env
 */
void	init_shell(char **env)
{
	char	*shlvl;

	shlvl = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 5) == 0)
			shlvl = *env + 6;
		env++;
	}
	if (shlvl)
		setenv("SHLVL", ft_itoa(ft_atoi(shlvl) + 1), 1); // forbidden function
	// else set SHLVL ?
}
