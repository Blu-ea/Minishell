/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:53:47 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 09:53:19 by amiguez          ###   ########.fr       */
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

# define PROMT "$minishell>"
# define PROMT_E "minishell:"

# define ENV_NOTSET 0	//Don t exist in env
# define ENV_UNSET 1	//Is in env but don t have a variable(No '=' next to it)
# define ENV_SET 2		//Is set in env with a variable (maybe empty)

/********************************/
/*				BUILTIN			*/
/********************************/

int		bin_cd(char *path, char **env);		//in progress
int		bin_pwd(void);						//Done
int		bin_echo(char **args);				//Done
int		bin_env(char **env);				//Done
int		bin_exp(char **args, char **env);
int		bin_unset(char **args, char **env);
int		bin_exit(char **args);				//Done

/********************************/
/*				Main			*/
/********************************/

char	*ft_read_line(void);
void	ft_clear_line(void);
void	init_env(char **env);
int		built_in(char *line, char **env);


/********************************/
/* 				Pars			*/
/********************************/


/********************************/
/* 				Env				*/
/********************************/

char	**env_init(char **env);
char	**env_add(char **env, char *name, char *desc);
char	**env_sub(char **env, char *name);

/*  Debug  */

void	print_env(char **env);

#endif