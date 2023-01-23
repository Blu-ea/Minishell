/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:01 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/23 20:42:41 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include "minishell.h"

/**
 * @brief Open the file name and return the file descriptor
 * 
 * @param pipe: The pipe to get the file name from
 * @param c: The type of redirect (>, <, a)
 * @return the file descriptor or -1 if an error occured or if the file name is
 * missing
 */
int	open_fd(char **pipe, char c)
{
	if (!pipe[0])
	{
		errno = 5;
		return (-1);
	}
	if (c == '>')
		return (open(pipe[0] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (c == '<')
		return (open(pipe[0] + 1, O_RDONLY));
	else
		return (open(pipe[0] + 1,
				O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644));
}

/**
 * @brief Open the file name and add the file descriptor to fds
 * 
 * @param pipe: The pipe to get the file name from
 * @param fds: The list of file descriptor
 * @param i: The index of the redirect
 * @param append_mode: 1 if the redirect is >>, 0 otherwise
 * @return 1 if an error occured, 0 otherwise
 */
char	get_fds(char **pipe, int *fds, int i, char append_mode)
{
	char	c;

	c = pipe[i][1];
	if (fds[c == '>'] != (c == '>'))
		close(fds[c == '>']);
	if (append_mode)
		fds[c == '>'] = open_fd(pipe + i + 1, 'a');
	else
		fds[c == '>'] = open_fd(pipe + i + 1, c);
	errno = 0;
	if (fds[c == '>'] == -1)
		return (1);
	return (0);
}

void	read_heredoc(char *str, int fd, char **env)
{
	char	*line;

	g_error_sig = IN_HEREDOC;
	line = NULL;
	while (1)
	{
		line = readline(">");
		ft_strlen(str);
		if (!line || ft_strncmp(line, str, ft_strlen(str) + 1) == 0)
			break ;
		line = handle_dollar_variable(line, env);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line)
		free(line);
	g_error_sig = 0;
}

int	heredoc(char **str, int *fds, char ***pipes, t_pipe *pipe_lst)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(pipefd[0]);
		pipe_lst->env = unset_del(pipe_lst->env, "?");
		read_heredoc((*str) + 1, pipefd[1], pipe_lst->env);
		close(pipefd[1]);
		clear_split(pipe_lst->env);
		clear_pipes(pipes);
		clear_pipe_lst(pipe_lst, 0);
		ft_clear_line(NULL, IN_EXIT);
		exit(0);
	}
	close(pipefd[1]);
	fds[0] = pipefd[0];
	wait(&status);
	return (WEXITSTATUS(status));
}

/**
 * @brief Open file descriptor and remove redirect from pipe
 * 
 * @param pipe the pipe to get the redirect from
 * @param fds list of file descriptor
 * @param pipes list of pipes in case of failed heredoc
 * @param pipe_lst list of pipes in case of failed heredoc
 * @return the index of the redirect that failed or 0 if no error -1 if the
 * redirect is invalid
 */
int	get_redirect(char **p, int *fds, char ***pipes, t_pipe *pipe_lst)
{
	int		i;

	fds[0] = 0;
	fds[1] = 1;
	i = 0;
	while (p[i])
	{
		if (p[i][0] == '3')
		{
			if (ft_strlen(p[i] + 1) > 2 || !p[i + 1] || p[i + 1][0] == '3'
				|| (p[i][1] != p[i][2] && p[i][2] != 0))
				return (-1);
			else if (p[i][1] == '<' && p[i][2] == '<')
			{
				if (heredoc(p + i + 1, fds, pipes, pipe_lst))
					return (-1);
			}
			else if (get_fds(p, fds, i, p[i][2]))
				return (i);
			i = remove_redirect(p, i);
		}
		i++;
	}
	return (0);
}
