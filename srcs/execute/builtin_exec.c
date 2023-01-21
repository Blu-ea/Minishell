/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:03:56 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/21 17:16:19 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"


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

int	run_built_in(int ret, t_pipe **pipe_lst, char ***envp, char pre_pipe)
{
	if (ret == 1 && pre_pipe)
	{
		clear_split(*envp);
		clear_pipe_lst(*pipe_lst, 1);
		bin_exit((*pipe_lst)->args + 1); //FIXME: cannot access args from free memory
	}
	else if (ret == 2 && pre_pipe)
		return (bin_cd((*pipe_lst)->args + 1, *envp));
	else if (ret == 3 && pre_pipe)
	{
		*envp = bin_export((*pipe_lst)->args + 1, envp, &ret);
		return (ret);
	}
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
