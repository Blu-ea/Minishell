/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 06:20:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 03:47:30 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	update_env(char **env);
int	cd_error(void);

/*
	if Path empty -> go to $HOME
		Si $HOME not set -> minishell: cd: $HOME not set
	
	update PWD with new location /!\ Do not create PWD if un_defined /!\
	update OLDPWD with old PWD /!\ Do not create OLDPWD if un_defined /!\
	take only 1 arg (ignore the other)
*/

int	bin_cd(char *path, char **env)
{
	char	temp[PATH_MAX];

	print_env(env);
	if (access(path, F_OK) == 0)
		chdir(path);
	else
	{
		if (getcwd(temp, PATH_MAX))
			return (cd_error());
		ft_strjoin_free(temp, path, FREE_BOTH);
	}
	update_env(env);
	return (0);
}

int	update_env(char **env)
{
	(void)env;
	return (0);
}

int	cd_error(void)
{
	printf("%s cd: failed\n", PROMT_E);
	return (1);
}
