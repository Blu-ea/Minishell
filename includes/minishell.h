/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:53:47 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/05 11:18:29 by amiguez          ###   ########.fr       */
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

/********************************/
/*				BUILTIN			*/
/********************************/

int		bin_cd(char *path, char **env);		//in progress
int		bin_echo(char **args);				//Done
int		bin_env(char **args, char **env);
int		bin_exp(char **args, char **env);
int		bin_pwd(char **args, char **env);
int		bin_unset(char **args, char **env);
void	bin_exit(char **args);				// base there

/********************************/
/*				Main			*/
/********************************/

char	*ft_read_line(void);
void	ft_clear_line(void);
void	init_env(char **env);

/********************************/
/* 				Pars			*/
/********************************/

/*  Debug  */

void	print_env(char **env);

#endif