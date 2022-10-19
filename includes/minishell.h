/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:53:47 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/19 06:59:13 by amiguez          ###   ########.fr       */
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
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <unistd.h>

# define PROMT "$minishell>"
# define PROMT_E "minishell:"

# define ENV_NOTSET 0	//Don t exist in env
# define ENV_UNSET 1	//Is in env but don t have a variable(No '=' next to it)
# define ENV_SET 2		//Is set in env with a variable (maybe empty)

/********************************/
/*				BUILTIN			*/
/********************************/

char	**bin_cd(char *path, char **env);				//in progress
int		bin_pwd(void);									//Done
int		bin_echo(char **args);							//Done
int		bin_env(char **env);							//Done
char	**bin_export(char **args, char ***env, int *ret);//in progress print done
void	print_t_export(char **env);				//for exports
int		ft_exp_print(char **env);				//for export
char	**bin_unset(char **args, char **env);
int		bin_exit(char **args);							//Done

/********************************/
/*				Main			*/
/********************************/

char	*ft_read_line(void);
void	ft_clear_line(void);
char	**init_env(char **env);
int		built_in(char *line, char ***env);

/********************************/
/* 				Pars			*/
/********************************/

/********************************/
/* 				Env				*/
/********************************/

int		env_is_set(char **env, char *name);
char	**env_init(char **env);

/*  Debug  */

int		test_export(char **env);

void	print_env(char **env);

#endif