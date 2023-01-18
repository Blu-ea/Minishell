/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:53:35 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/18 16:35:44 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

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

/**
 * @brief Remove the spaces(2) and merge texts(0, 1)
 * 
 * @param pipe: The address of the pipe to trim
 * @param i: random int for norme
 * @return 1 if an error occured, 0 otherwise 
 */
char	trim_pipe(char ***pipe, int i)
{
	int		j;
	char	*new_str;
	char	**new_pipe;

	new_pipe = ft_calloc(sizeof(*new_pipe), (new_pipe_len(*pipe) + 1));
	if (!new_pipe)
		return (1);
	i = -1;
	if (**pipe && (*pipe)[0][0] == '2')
		i++;
	j = -1;
	while ((*pipe)[++i])
	{
		new_str = ft_strdup((*pipe)[i] + 1);
		while ((*pipe)[i + 1] && (*pipe)[++i] && ((*pipe)[i][0] == '0'
			|| (*pipe)[i][0] == '1' || (*pipe)[i][0] == '3'))
			new_str = ft_newjoin(new_str, (*pipe)[i] + 1);
		if (!new_str)
			return (clear_pipe(new_pipe));
		new_pipe[++j] = new_str;
	}
	new_pipe[++j] = NULL;
	clear_pipe(*pipe);
	*pipe = new_pipe;
	return (0);
}
