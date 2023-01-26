/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:27 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/26 13:38:15 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(char **env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		path = env_get_value(env, "PWD");
	if (path == NULL)
	{
		ft_print_error("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
