/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:37:33 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/18 19:13:09 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/**
 * @brief Trim the pipe and convert it to a t_pipe and add it to the list
 * 
 * @param pipe_lst: The list of t_pipe to add the pipe to
 * @param pipe: The address of the pipe to add to the list
 * @param pipes: The array of pipes
 * @param i: The index of the pipe to convert in pipes
 * @return 1 if an error occured, 0 otherwise
 */
char	convert_to_t_pipe(t_pipe *pipe_lst, t_pipe **pipe, char ***pipes, int i)
{
	if (trim_pipe(pipes + i, -1))
		return (clear_error_pipe(pipe_lst, pipes));
	(*pipe)->args = pipes[i];
	(*pipe)->next = NULL;
	if (pipe_add_back(pipe, pipe_new(0, 0)))
		return (clear_error_pipe(pipe_lst, pipes));
	*pipe = (*pipe)->next;
	return (0);
}

/**
 * @brief a function to be under 25 lines
 * 
 * @param index 
 * @param pipe_lst 
 * @param pipes 
 * @return 1 or 0 depending if index is -1 or not
 */
char	handle_get_red(int index, t_pipe *pipe_lst, char ***pipes)
{
	if (index == -1)
		return (clear_error_pipe(pipe_lst, pipes));
	return (0);
}

/**
 * @brief Closes the file descriptor of the pipe that failed and prints the 
 * error. Adds a pipe with empty args to the list so there is no leaks.
 * 
 * @param tpipe: The new pipe to be filled
 * @param pipe: The pipe that failed
 * @param index: The index of the text that failed
 */
char	no_redirect(t_pipe **tpipe, char **pipe, int index)
{
	struct stat	buf;
	char		*tmp;

	if ((*tpipe)->fd[0] != 0 && (*tpipe)->fd[0] != -1)
		close((*tpipe)->fd[0]);
	if ((*tpipe)->fd[1] != 1 && (*tpipe)->fd[1] != -1)
		close((*tpipe)->fd[1]);
	(*tpipe)->fd[0] = 0;
	(*tpipe)->fd[1] = 1;
	if (!access(pipe[index + 1] + 1, F_OK))
	{
		stat(pipe[index + 1] + 1, &buf);
		if (S_ISDIR(buf.st_mode))
			errno = 21;
		else
			errno = 13;
	}
	else
		errno = 2;
	tmp = ft_strjoin("Redirect: ", pipe[index + 1] + 1);
	perror(tmp);
	free(tmp);
	errno = 0;
	return (disable_pipe(tpipe, pipe));
}

/**
 * @brief Execute pipes
 * 
 * @param pipes: array of pipes
 * @param envp: environment variables
 * @return the error code of the last command or -1 if there was no command or
 * errno if an error occured
 */
int	execute_pipes(char ***pipes, char **envp)
{
	int		i;
	int		index;
	t_pipe	*pipe_lst;
	t_pipe	*pipe;

	pipe_lst = pipe_new(0, 0);
	if (!pipe_lst)
		return (clear_pipes(pipes));
	pipe = pipe_lst;
	i = -1;
	while (pipes[++i])
	{
		index = get_redirect(pipes[i], pipe->fd, pipes, pipe_lst);
		if (index && handle_get_red(index, pipe_lst, pipes))
		{
			errno = 5;
			return (errno);
		}
		else if (index && no_redirect(&pipe, pipes[i], index))
			return (clear_error_pipe(pipe_lst, pipes));
		else if (!index && convert_to_t_pipe(pipe_lst, &pipe, pipes, i))
			return (errno);
		// print_pipe_struct(pipe_lst);
	}
	free(pipes);
	return (pipex(&pipe_lst, envp));
}
