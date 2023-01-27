/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 06:20:54 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 08:06:09 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

char	*cd_get_home(char **env, char *name);
char	*cd_transfo_path(char *path, char **env, char *name);

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

	new_path = follow_home(*path, env, "cd");
	if (new_path == NULL && !ft_strncmp("-", *path, 2))
		return (1);
	old_path = getcwd(NULL, 0);
	if (ft_strncmp(new_path, "", 1) && chdir(new_path) == -1)
	{
		ft_print_error2("cd", new_path);
		errno = 0;
		free(new_path);
		free(old_path);
		return (1);
	}
	if (!ft_strncmp("-", *path, 2))
		printf("%s\n", new_path);
	free(new_path);
	ret = cd_update_env(getcwd(NULL, 0), old_path, env);
	if (old_path)
		free(old_path);
	return (ret);
}

/**
 * @brief follow ~ and ~/ and return the correct path
 * 
 * @param path: path to transform
 * @param env: env to get $HOME
 * @param name: name of the function or null
 * @return The new path or NULL if error
 */
char	*follow_home(char *path, char **env, char *name)
{
	int	i;

	if (path == 0 || !ft_strncmp(path, "~", 2) || \
			!ft_strncmp(path, "~/", 3))
		return (cd_get_home(env, name));
	if (!ft_strncmp(path, "~/", 2))
		return (cd_transfo_path(path, env, name));
	if (!ft_strncmp("-", path, 2) && !ft_strncmp("cd", name, 2))
	{
		i = env_is_set(env, "OLDPWD");
		if (i == ENV_SET)
			path = env_get_value(env, "OLDPWD");
		else
			return (cd_error(NO_OLDPWD, "cd"), NULL);
		return (path);
	}
	return (ft_strdup(path));
}

char	*cd_get_home(char **env, char *name)
{
	char	*temp;
	char	*ret;

	if (env_is_set(env, "HOME") == ENV_NOTSET)
		return (cd_error(NO_HOME, name));
	if (env_is_set(env, "HOME") == ENV_UNDIFINED)
		return (ft_strdup(""));
	temp = env_get_value(env, "HOME");
	ret = ft_strdup(temp);
	if (!temp || !ret)
		return (cd_error(MALLOC_ERROR, name));
	free (temp);
	return (ret);
}

char	*cd_transfo_path(char *path, char **env, char *name)
{
	char	*temp;
	char	*ret;

	if (env_is_set(env, "HOME") == ENV_NOTSET)
		return (cd_error(NO_HOME, name));
	if (env_is_set(env, "HOME") == ENV_UNDIFINED)
		return (ft_strdup(path));
	temp = env_get_value(env, "HOME");
	if (!temp)
		return (cd_error(MALLOC_ERROR, name));
	ret = ft_strjoin(temp, path + 1);
	free (temp);
	if (!ret)
		return (cd_error(MALLOC_ERROR, name));
	return (ret);
}

char	*cd_error(int err, char *name)
{
	if (err == TO_MANY_ARGS)
		ft_print_error2(name, "too many arguments");
	if (err == NO_HOME)
		ft_print_error2(name, "HOME not set");
	if (err == NO_OLDPWD)
		ft_print_error2(name, "OLDPWD not set");
	if (err == MALLOC_ERROR)
		ft_print_error2(name, "Something went wrong");
	return (NULL);
}
