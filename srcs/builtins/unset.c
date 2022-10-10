/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:51:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/08 09:42:46 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cannot unset _
*/

char	**bin_unset(char **args, char **env)
{
	(void)env;
	(void)args;
	return (NULL);
}

char	**env_del(char **env, char *name)
{
	(void)env;
	(void)name;
	return (NULL);
}
