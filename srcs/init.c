/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 05:38:29 by jcollon           #+#    #+#             */
/*   Updated: 2022/06/29 17:06:33 by amiguez          ###   ########.fr       */
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
	// faire un execve avec (export (SHLVL=ft_atoi(shlvl) + 1))
	//if (shlvl == NULL) export "SHLVL=1"
}
