/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:53:47 by amiguez           #+#    #+#             */
/*   Updated: 2022/07/03 10:09:56 by amiguez          ###   ########.fr       */
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

# define PROMT "$minishell>"

# define EMPTY_LINE -1

typedef struct s_cmd	t_cmd;

typedef struct s_shel
{
	int		nb_cmd;
	t_cmd	*cmd;
	char	**env;
}		t_shel;

typedef struct s_cmd
{
	char	*infile;
	char	*cmd;
	char	**args;
	char	*outfile;
}		t_cmd;
void	init_shell(char **env);
int		split_mini(char *line, t_shel *data);
int		ft_pars(char **env, t_shel *data);

int		split_mini(char *line, t_shel *data);
int		ft_count_pipe(char *line);
void	ft_clear_data(t_shel *data);

/********************************
 * 			BuiltIn				*
 ********************************/

void	ft_cd(t_shel *data);
void	ft_echo(t_shel *data);
void	ft_env(t_shel *data);
void	ft_exit(t_shel *data);
void	ft_export(t_shel *data);
void	ft_pwd(t_shel *data);
void	ft_unset(t_shel *data);

/********************************
 * 				Pars			*
 ********************************/

#endif