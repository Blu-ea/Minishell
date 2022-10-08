/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 06:20:54 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/08 10:01:37 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

char	**update_env(char **env);
char	**cd_error(void);

/*
	if Path empty -> go to $HOME
		Si $HOME not set -> minishell: cd: $HOME not set
	
	update PWD with new location /!\ Do not create PWD if un_defined /!\
	update OLDPWD with old PWD /!\ Do not create OLDPWD if un_defined /!\
	take only 1 arg (ignore the other)
*/

char**	bin_cd(char *path, char **env)
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
	return (env);
}

char	**update_env(char **env)
{
	(void)env;
	return (NULL);
}

char	**cd_error(void)
{
	printf("%s cd: failed\n", PROMT_E);
	return (NULL);
}
