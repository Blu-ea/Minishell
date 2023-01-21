/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:03:56 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/21 23:39:42 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

/**
 * @brief Return if the command is a built in (>0) or a command to rewrite (<0)
 * 
 * @param cmd the command
 * @return 1=exit | 2=cd | 3=export | 4=unset | -1=env | -2=echo | -3=pwd
 */
int	is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	else if (!ft_strncmp(cmd, "export", 7))
		return (3);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (4);
	else if (!ft_strncmp(cmd, "env", 4))
		return (-1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (-2);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (-3);
	return (0);
}

int	rebin_export(char **args, char ***envp)
{
	int		ret;

	*envp = bin_export(args, envp, &ret);
	return (ret);
}

/**
 * @brief Execute the built in
 * 
 * @param ret the return of is_built_in
 * @param pipe_lst the pipe list
 * @param envp the environment
 * @param pre_pipe if the command is before the fork
 * @return the return of the built in
 */
int	run_built_in(int ret, t_pipe **pipe_lst, char ***envp, char pre_pipe)
{
	if (ret == 1 && pre_pipe)
	{
		ret = bin_exit((*pipe_lst)->args + 1, *envp);
		if (ret >= 0)
		{
			clear_split(*envp);
			clear_pipe_lst(*pipe_lst, 1);
			exit(ret);
		}
		return (-ret);
	}
	else if (ret == 2 && pre_pipe)
		return (bin_cd((*pipe_lst)->args + 1, *envp));
	else if (ret == 3 && pre_pipe)
		return (rebin_export((*pipe_lst)->args + 1, envp));
	else if (ret == 4 && pre_pipe)
		return (bin_unset((*pipe_lst)->args + 1, envp));
	else if (ret == -1 && !pre_pipe)
		return (bin_env(*envp));
	else if (ret == -2 && !pre_pipe)
		return (bin_echo((*pipe_lst)->args + 1));
	else if (ret == -3 && !pre_pipe)
		return (bin_pwd());
	return (0);
}
