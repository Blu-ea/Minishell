/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:54:56 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/19 15:49:16 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>

typedef struct s_pipe
{
	int				fd[2];
	char			**args;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_fd_lst
{
	int				fd;
	struct s_fd_lst	*next;
}	t_fd_lst;

void		print_pipe_struct(t_pipe *pipe);
void		print_command(char ***pipes);
void		print_pipe(char	**pipe, char nl);
void		check_fd_leak(void);

void		trim_prefix(char **pipe);

char		*add_prefix(const char *s1, char *s2);

int			pipex(t_pipe **pipe_lst, char **envp);

int			get_redirect(char **pipe, int *fds, char ***pipes,
				t_pipe *pipe_lst);

int			remove_redirect(char **pipe, int i);
char		disable_pipe(t_pipe **tpipe, char **pipe);

t_pipe		*pipe_last(t_pipe *lst);
t_pipe		*pipe_new(char **args, int *fd);
char		pipe_add_back(t_pipe **lst, t_pipe *new);

t_fd_lst	*fd_lst_new(int fd);
char		fd_lst_add_front(t_fd_lst **lst, t_fd_lst *new);

void		clear_pipe_lst(t_pipe *pipe, char clear_args);
int			clear_pipe(char **pipe);
int			clear_pipes(char ***pipe);
void		*clear_split(char **split);
char		clear_error_pipe(t_pipe *pipe_lst, char ***pipes);

// char		free_return(void *str, char ret);
char		cmd_not_found(char *cmd);
void		error_execve(char ret, t_pipe *pipe, t_fd_lst *std_ins,
				t_fd_lst *pids);
void		free_fds(t_fd_lst *std_in, t_fd_lst *pids);

int			pipex(t_pipe **pipe_lst, char **envp);

int			execute_pipes(char ***pipes, char **envp);

int			launch_prog(t_pipe *pipe, char **envp, t_fd_lst **std_ins,
				t_fd_lst **pids);

void		ft_exit(const char *str, int exit_code);
#endif // PIPE_H
