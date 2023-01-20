/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:55:22 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/20 23:36:24 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	free_return(void *str, char ret)
{
	free(str);
	return (ret);
}

/**
 * @brief Print to stderr 'cmd': command not found
 * 
 * @param cmd: The command that was not found
 * @return 2
 */
char	cmd_not_found(char *cmd)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (2);
	}
	return (0);
}

/**
 * @brief Free the pipe list and exit with the error message
 * 
 * @param ret: 1 if an error occured, 2 if the command was not found
 * @param pipe: The pipe list
 * @param std_ins: The list of standard input
 * @param pids: The list of pid
 */
void	error_execve(char ret, t_pipe *pipe, t_fd_lst *std_ins, t_fd_lst *pids)
{
	clear_pipe_lst(pipe, 1);
	free_fds(std_ins, pids);
	if (ret == 1)
		ft_exit("Error: ", 1);
	exit(127);
}

/**
 * @brief Free the standard input list and the list of pid if it exists
 * 
 * @param std_in: List of standard input file descriptor
 * @param pids: List of pid
 */
void	free_fds(t_fd_lst *std_in, t_fd_lst *pids)
{
	t_fd_lst	*temp;

	while (std_in)
	{
		if (std_in->fd != 0 && std_in->fd != 1 && std_in->fd != 2)
			close(std_in->fd);
		temp = std_in->next;
		free(std_in);
		std_in = temp;
	}
	if (pids)
	{
		while (pids)
		{
			temp = pids->next;
			free(pids);
			pids = temp;
		}
	}
}
