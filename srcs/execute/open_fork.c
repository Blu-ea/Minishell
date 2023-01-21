/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:01:30 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/21 22:02:21 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/**
 * @brief SAFE Open a pipe and a fork safely
 * 
 * @param pipefd: list of the stdin and stdout of the pipe
 * @param pip: the current pipe to reset if an error occured
 * @return the pid of the child or -1 if the command had an error
 */
pid_t	open_fork(int pipefd[2], t_pipe *pip)
{
	pid_t	pid;

	if (pip->args[0] == 0)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		free(pip->args[0]);
		pip->args[0] = 0;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		free(pip->args[0]);
		pip->args[0] = 0;
		return (-1);
	}
	return (pid);
}
