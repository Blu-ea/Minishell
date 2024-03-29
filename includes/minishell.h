/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:53:47 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/27 10:27:58 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
// # include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <unistd.h>

# define PROMT "$minishell> "
# define PROMT_E "minishell"
# define ENV_NOTSET 0	//Don t exist in env
# define ENV_UNDIFINED 1//Is in env but don t have a variable(No '=' next to it)
# define ENV_SET 2		//Is set in env with a variable (maybe empty)

# define NO_ARGS 0
# define ARGS 1

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define TO_MANY_ARGS 1
# define WRONG_PATH 2
# define NO_HOME 3
# define NO_OLDPWD 4
# define MALLOC_ERROR 10

# define C_C_CALL 1
# define IN_HEREDOC 2
# define LAUNCHED_HEREDOC 3
# define IN_READLINE 4
# define CHILD 5
# define C_C_HEREDOC 6
# define C_BACK 7

# define NOT_IN_EXIT 1
# define IN_EXIT 0
# define NOT_IN_PIPE 1
# define IN_PIPE 0

# include "parse.h"

int		g_error_sig;

/********************************/
/*				BUILDIN			*/
/********************************/

int		bin_cd(char **path, char **env);
char	*cd_error(int err, char *name);
int		cd_update_env(char *new_path, char *old_path, char **env);
char	*follow_home(char *path, char **env, char *name);
int		bin_pwd(char **env);
int		bin_echo(char **args);
int		bin_env(char **env);
char	**bin_export(char **args, char ***env, int *ret);
char	**env_add(char **env, char *args);
char	**exp_update(char **env, char *args);
void	print_t_export(char **env);
int		bin_unset(char **args, char ***env);
char	**unset_del(char **env, char *arg);
int		bin_exit(char **args, char **env);

/********************************/
/*		for BUILDIN in pipes	*/
/********************************/

int		bin_pipe_exit(char **arg);
int		bin_pipe_cd(char **path, char **env);
int		bin_pipe_export(char **args, char ***env);
int		bin_pipe_unset(char **args, char ***env);

/********************************/
/*				Main			*/
/********************************/

char	*ft_read_line(char **env);
void	ft_clear_line(char *new_history, int i);
int		built_in(char **args, char ***env);
void	ft_print_error(char *str);
void	ft_print_error2(char *str, char *str2);

/********************************/
/* 				Env				*/
/********************************/

int		env_is_set(char **env, char *name);
char	**env_init(char **env);
char	*env_get_value(char **env, char *name);

char	**init_up_env(char **env);
char	**init_env(char **env);

/********************************/
/* 				SIG				*/
/********************************/

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	sigint_inpipe(int sig);

/*  Debug  */

void	print_env(char **env);

#endif