/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:54:56 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 14:40:32 by jcollon          ###   ########lyon.fr   */
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
	char			**env;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_fd_lst
{
	int				fd;
	struct s_fd_lst	*next;
}	t_fd_lst;

/* ********************************EXECUTION********************************* */
int			execute_pipes(char ***pipes, char ***envp);
int			get_redirect(char **pipe, int *fds, char ***pipes,
				t_pipe *pipe_lst);
int			pipex(t_pipe **pipe_lst, char ***envp);
int			launch_prog(t_pipe *pipe, char **envp, t_fd_lst **std_ins);
pid_t		open_fork(int pipefd[2], t_pipe *pip);
int			is_built_in(char *cmd);
int			run_built_in(int ret, t_pipe **pipe_lst, char ***envp,
				char pre_pipe);

/* **********************************PREFIX********************************** */
void		trim_prefix(char **pipe);
char		*add_prefix(const char *s1, char *s2);

/* **********************************UTILS*********************************** */
int			remove_redirect(char **pipe, int i);
char		disable_pipe(t_pipe **tpipe, char **pipe);

/* *******************************t_pipe UTILS******************************* */
t_pipe		*pipe_new(char **args, int *fd, char **env);
int			pipe_len(t_pipe *lst);
t_pipe		*pipe_last(t_pipe *lst);
char		pipe_add_back(t_pipe **lst, t_pipe *new_lst);

/* *******************************fd_lst UTILS******************************* */
t_fd_lst	*fd_lst_new(int fd);
char		fd_lst_add_front(t_fd_lst **lst, t_fd_lst *new_lst);
t_fd_lst	*fd_lst_del_one(t_fd_lst *lst);

/* ***********************************EXIT*********************************** */
int			cmd_not_found(char *cmd, int exit_code);
void		error_execve(char ret, t_pipe *pipe, t_fd_lst *std_ins,
				t_fd_lst *pids);
void		free_fds(t_fd_lst *std_in, t_fd_lst *pids);
void		clear_pipe_lst(t_pipe *pipe, char clear_args);
int			clear_pipe(char **pipe);
int			clear_pipes(char ***pipe);
char		clear_split(char **split);
char		clear_error_pipe(t_pipe *pipe_lst, char ***pipes);

#endif // PIPE_H
