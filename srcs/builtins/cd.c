/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 06:20:54 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/23 18:23:07 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

char	*found_path(char **path, char **env);
char	*cd_get_home(char **env);
char	*cd_transfo_path(char *path, char **env);

/*
	if Path empty -> go to $HOME
		Si $HOME not set -> minishell: cd: $HOME not set
	
	update PWD with new location /!\ Do not create PWD if un_defined /!\
	update OLDPWD with old PWD /!\ Do not create OLDPWD if un_defined /!\
	take only 1 arg (ignore the other)

	1 Check if path is correct 
		if not -> error
		if empty -> go to $HOME
			if $HOME not set -> error
	2 update OLPWD if initialized
	3 move to new path
	4 update PWD if initialized
*/
int	bin_cd(char **path, char **env)
{
	char	*new_path;
	char	*old_path;
	int		ret;

	new_path = found_path(path, env);
	if (new_path == NULL)
		return (1);
	old_path = getcwd(NULL, 0);
	if (chdir(new_path) == -1)
	{
		ft_print_error2("cd", new_path);
		free(new_path);
		free(old_path);
		return (1);
	}
	free(new_path);
	ret = cd_update_env(getcwd(NULL, 0), old_path, env);
	free(old_path);
	return (ret);
}

char	*found_path(char **path, char **env)
{
	if (path[0] == 0 || !ft_strncmp(path[0], "~", 2) || \
			!ft_strncmp(path[0], "~/", 3))
		return (cd_get_home(env));
	if (path[1] != 0)
		return (cd_error(TO_MANY_ARGS));
	if (!ft_strncmp(path[0], "~/", 2))
		return (cd_transfo_path(path[0], env));
	return (ft_strdup(path[0]));
}

char	*cd_get_home(char **env)
{
	char	*temp;
	char	*ret;

	if (env_is_set(env, "HOME") == ENV_NOTSET)
		return (cd_error(NO_HOME));
	if (env_is_set(env, "HOME") == ENV_UNDIFINED)
		return (ft_strdup(""));
	temp = env_get_value(env, "HOME");
	ret = ft_strjoin("/", temp);
	if (!temp || !ret)
		return (cd_error(MALLOC_ERROR));
	free (temp);
	return (ret);
}

char	*cd_transfo_path(char *path, char **env)
{
	char	*temp;
	char	*ret;

	if (env_is_set(env, "HOME") == ENV_NOTSET)
		return (cd_error(NO_HOME));
	if (env_is_set(env, "HOME") == ENV_UNDIFINED)
		return (ft_strdup(path));
	temp = env_get_value(env, "HOME");
	if (!temp)
		return (cd_error(MALLOC_ERROR));
	ret = ft_strjoin(temp, path + 1);
	free (temp);
	if (!ret)
		return (cd_error(MALLOC_ERROR));
	return (ret);
}

char	*cd_error(int err)
{
	write(2, PROMT_E, ft_strlen(PROMT_E));
	if (err == TO_MANY_ARGS)
		write(2, " cd: too many arguments\n", 25);
	if (err == NO_HOME)
		write(2, " cd: HOME not set\n", 19);
	if (err == MALLOC_ERROR)
		write(2, " cd: Something went wrong\n", 27);
	return (NULL);
}
