/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:21:55 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 02:03:30 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <errno.h>
# include "../libft/includes/libft.h"

/* **********************************DEBUG*********************************** */
void		print_pipe(char	**pipe, char nl);
void		print_command(char ***pipes);
void		print_cutting_index(int *cutting_index);
char		*add_red(char *str, int i);

/* **********************************PARSE*********************************** */
char		***parse(char *str, char **env);
char		quote_error(char *str);
int			number_of_pipes(char **str);

/* *********************************HANDLERS********************************* */
char		*handle_dollar_variable(char *str, char **env);
char		handle_dollar_variables(char **cmd, char **env);
char		handle_double_quotes(char ***cmd);
char		handle_white_space(char ***cmd);
char		handle_pipes(char ***cmd);
char		handle_redirect(char ***cmd);

/* ********************************GET_INDEX********************************* */
int			*get_index_single_quotes(char *str);
int			*get_index_double_quotes(char *str);
int			*get_index_white_space(char *str);
int			*get_index_redirect(char *str);
int			*get_index_pipe(char *str);

/* *********************************CUT_CMD********************************** */
int			cmd_parts(char *str, int *indexs);
char		**cut_command(char *str, int *indexs);
char		**cut_cmd_space(char *str, int *indexs);
char		**cut_cmd_redirect(char *str, int *indexs);
char		**cut_cmd_pipe(char *str, int *indexs);

/* **********************************UTILS*********************************** */
char		*ft_join3(char *s1, const char *s2, char *s3);
char		*add_prefix(const char *s1, char *s2);
int			ft_inttablen(int *tan);
int			*append_int(int *tab, int nb);
char		**insert(char **tab, char *str, int pos);
int			size_pipe(char **pipe, int index);
void		clean_empty(char ***cmd);
int			split_merge_cmd(char ***pipe, int *indexs, int index,
				char **(*cut)(char *, int *));

/* ***********************************EXIT*********************************** */
int			clear_pipes(char ***pipes);
int			clear_pipe(char **pipe);
char		***clear_error_pipes(char ***pipes, char **cmd, int i);
char		**check_fail_cut_cmd(char **ret, int j);
char		free_return(void *ptr, int ret);

/* ***********************************MISC*********************************** */
char		trim_pipe(char ***pipe);
char		precheck(char *str);
char		***split_pipes(char **cmd);

#endif // PARSE_H