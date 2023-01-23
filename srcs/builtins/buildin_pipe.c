/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:00:20 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/23 18:56:50 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_path(char **path, char **env);
int		exit_alpha(char *temp, char **arg, int pipe);
void	ret_exp_update(int *ret);

int	bin_pipe_exit(char **arg)
{
	int		ret;
	char	*temp;

	if (arg == NULL || !*arg)
		return (0);
	ret = ft_atoi(*arg);
	temp = ft_itoa(ret);
	if (ft_strncmp(temp, arg[0], ft_strlen(arg[0])) != 0)
		return (exit_alpha(temp, arg, IN_PIPE));
	free(temp);
	temp = *arg;
	while (*arg)
		arg++;
	arg--;
	if (temp - *arg != 1 && temp - *arg != 0)
	{	
		ft_print_error2("exit", "too many arguments");
		return (1);
	}
	return (ret % 256);
}

int	bin_pipe_cd(char **path, char **env)
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

int	bin_pipe_export(char **args, char ***env)
{
	int		i;
	int		ret;

	i = 0;
	if (!*args)
		print_t_export(*env);
	while (args[i])
	{
		ret = env_is_set(*env, args[i]);
		if (ret == -2)
		{
			write (2, PROMT_E, ft_strlen(PROMT_E));
			write (2, " :export : `", 13);
			write (2, args[i], ft_strlen(args[i]));
			write (2, "': not a valid identifier\n", 27);
		}
		i++;
	}
	ret_exp_update(&ret);
	return (ret + 1);
}

int	bin_pipe_unset(char **args, char ***env)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	if (!*args)
		return (ret);
	while (args[++i])
	{
		ret = env_is_set(*env, args[i]);
		if (ret == -2)
		{
			write (2, PROMT_E, ft_strlen(PROMT_E));
			write (2, " :export : `", 13);
			write (2, args[i], ft_strlen(args[i]));
			write (2, "': not a valid identifier\n", 27);
		}
		i++;
	}
	return (ret);
}
