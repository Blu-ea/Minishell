/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:55:22 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/26 21:32:37 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

/**
 * @brief Print to stderr 'cmd': command not found
 * 
 * @param cmd: The command that was not found
 * @return 1 if it is a execve error, 2 if the command was not found, 3 if it is
 * a directory, 4 if HOME is not set and was needed, 0 if the command didn't
 * execute
 */
char	cmd_not_found(char *cmd, int exit_code)
{
	if (cmd && exit_code == -1)
		return (1);
	else if (cmd && exit_code == 0)
	{
		ft_putstr_fd(PROMT_E, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (2);
	}
	else if (cmd && (exit_code == -126))
		return (3);
	else if (cmd && exit_code == -2)
		return (4);
	return (0);
}

/**
 * @brief Free the pipe list and exit with the error message
 * 
 * @param ret: 1 if an error occured, 2 if the command was not found 3 if it is
 * a directory, 4 if HOME is not set and was needed
 * @param pipe: The pipe list
 * @param std_ins: The list of standard input
 * @param pids: The list of pid
 */
void	error_execve(char ret, t_pipe *pipe, t_fd_lst *std_ins, t_fd_lst *pids)
{
	clear_pipe_lst(pipe, 1);
	free_fds(std_ins, pids);
	ft_clear_line(NULL, IN_EXIT);
	if (ret == 2)
		exit(127);
	else if (ret == 3)
		exit(126);
	else if (ret == 4)
		exit(1);
	else
	{
		perror(PROMT_E);
		exit(errno);
	}
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
	while (pids)
	{
		temp = pids->next;
		free(pids);
		pids = temp;
	}
}
