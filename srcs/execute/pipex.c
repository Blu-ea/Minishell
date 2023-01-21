/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:28:24 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/21 16:11:56 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"
#include <sys/wait.h>

/**
 * @brief Wait for all the pid in the list
 * and close the standard input of the next command
 * 
 * @param pids: List of pid
 * @return The status code of the last command
 */
int	wait_pids(t_fd_lst **pids)
{
	t_fd_lst	*lst;
	int			pid;

	if (!(*pids)->fd)
		return (0);
	lst = (*pids);
	waitpid(lst->fd, &pid, 0);
	lst = lst->next;
	while (lst && lst->next)
	{
		waitpid(lst->fd, NULL, 0);
		lst = lst->next;
	}
	return (WEXITSTATUS(pid));
}

/**
 * @brief Launch a pipe and adds the pid to the list
 * 
 * @param pipe: the pipe to launch
 * @param envp: the environment variable
 * @param std_ins: the list of standard input
 * @param pids: the list of pid
 * @return 1 if an error occured, 2 if the command was not found, 0 otherwise
 */
char	launch_pipe(t_pipe *pipe, char **envp, t_fd_lst **std_ins,
	t_fd_lst **pids)
{
	t_fd_lst	*tmp;

	if (fd_lst_add_front(pids, fd_lst_new(launch_prog(pipe, envp, std_ins)))
		|| (*pids)->fd <= 0)
	{
		if ((*pids)->fd == 0)
		{
			tmp = (*pids)->next;
			free(*pids);
			*pids = tmp;
			if (fd_lst_add_front(std_ins,
					fd_lst_new(open("/dev/null", O_RDONLY))))
				return (1);
			errno = 0;
			return (cmd_not_found(pipe->args[0]));
		}
		else
			return (1);
	}
	return (0);
}

char	is_built_in(t_pipe **pipe_lst, char **envp)
{
	if (pipe_len(*pipe_lst) == 2)
	{
		if (!ft_strncmp((*pipe_lst)->args[0], "exit", 5))
		{
			clear_split(envp);
			clear_pipe_lst(*pipe_lst, 1);
			bin_exit((*pipe_lst)->args);
		}
		else if (!ft_strncmp((*pipe_lst)->args[0], "cd", 3))
			return (1);
		else if (!ft_strncmp((*pipe_lst)->args[0], "export", 7))
			return (2);
		else if (!ft_strncmp((*pipe_lst)->args[0], "unset", 6))
			return (3);
	}
	return (0);
}

int	run_built_in(t_pipe **pipe_lst, char ***envp)
{
	int	ret;

	ret = is_built_in(pipe_lst, *envp);
	if (ret == 1)
		return (bin_cd((*pipe_lst)->args + 1, *envp));
	else if (ret == 2)
	{
		*envp = bin_export((*pipe_lst)->args + 1, envp, &ret);
		return (ret);
	}
	else if (ret == 3)
		return (bin_unset((*pipe_lst)->args + 1, envp));
	return (0);
}

/**
 * @brief Launch all the command in the pipe list
 * 
 * @param pipe_lst: the pipe list
 * @param envp: the environment
 * @return int the status code of the last command
 */
int	pipex(t_pipe **pipe_lst, char ***envp)
{
	t_fd_lst	*std_ins;
	t_fd_lst	*pids;
	t_pipe		*pipe;
	char		tmp;
	int			ret;

	if (is_built_in(pipe_lst, *envp))
		return (run_built_in(pipe_lst, envp));
	pids = fd_lst_new(0);
	std_ins = fd_lst_new(0);
	pipe = *pipe_lst;
	ret = 0;
	while (pipe->next)
	{
		tmp = launch_pipe(pipe, *envp, &std_ins, &pids);
		if (tmp)
			error_execve(tmp, *pipe_lst, std_ins, pids);
		pipe = pipe->next;
		ret++;
	}
	ret = wait_pids(&pids);
	clear_pipe_lst(*pipe_lst, 1);
	free_fds(std_ins, pids);
	return (ret);
}
