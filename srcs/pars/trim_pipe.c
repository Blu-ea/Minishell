/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:18:10 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/27 00:04:01 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_newjoin(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	if (s1)
		free(s1);
	return (ret);
}

/**
 * @brief Calculate the length of the new pipe after trimming
 * 
 * @param pipe: The pipe to calculate
 * @return int 
 */
int	new_pipe_len(char **pipe)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (pipe[++i])
	{
		while (pipe[i + 1] && (pipe[i][0] == '0' || pipe[i][0] == '1'))
			i++;
		ret++;
	}
	return (ret);
}

char	*join_pipe(char *new_str, char **pipe, int *i)
{
	if (pipe[*i][0] == '0' || pipe[*i][0] == '1')
	{
		while (pipe[*i] && pipe[++(*i)] && (pipe[*i][0] == '0'
			|| pipe[*i][0] == '1'))
			new_str = ft_newjoin(new_str, pipe[*i] + 1);
	}
	else
		(*i)++;
	return (new_str);
}

/**
 * @brief Remove the spaces(2) and merge texts(0, 1)
 * 
 * @param pipe: The address of the pipe to trim
 * @return 1 if an error occured or if a pipe is empty, 0 otherwise 
 */
char	trim_pipe(char ***pipe)
{
	int		i;
	int		j;
	char	*new_str;
	char	**new_pipe;

	new_pipe = ft_calloc(sizeof(*new_pipe), (new_pipe_len(*pipe) + 2));
	if (!new_pipe || (!pipe[0][0] && free_return(new_pipe, 1)))
		return (1);
	i = 0;
	j = -1;
	while ((*pipe)[i] && !((*pipe)[i][0] == '2' && !(*pipe)[i + 1]))
	{
		while ((*pipe)[i] && (*pipe)[i + 1] && (*pipe)[i][0] == '2')
			++i;
		new_str = ft_strdup((*pipe)[i]);
		new_str = join_pipe(new_str, *pipe, &i);
		if (!new_str || (!new_str[0] && free_return(new_str, 1)))
			return (clear_pipe(new_pipe));
		new_pipe[++j] = new_str;
	}
	if (!new_pipe[0] && clear_pipe(new_pipe))
		return (1);
	clear_pipe(*pipe);
	*pipe = new_pipe;
	return (0);
}

char	error_pipe(void)
{
	if (errno)
	{
		perror("Error");
		return (1);
	}
	printf("parse: syntax error near unexpected token `|'\n");
	return (1);
}
