/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:12:24 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/17 18:07:05 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipe(char	**pipe, char nl)
{
	int	i;
	int	debug;

	debug = 1; // 0 = debug, 1 = no debug
	i = -1;
	printf("[");
	while (pipe[++i])
	{
		if (pipe[i][0] == '0')
			printf("\"\x1B[31m");
		else if (pipe[i][0] == '1')
			printf("\"\x1B[32m");
		else if (pipe[i][0] == '2')
			printf("\"\x1B[41m");
		else if (pipe[i][0] == '3')
			printf("\"\x1B[34m");
		else if (pipe[i][0] == '4')
			printf("\"\x1B[43m");
		else
		{
			printf("\"\x1B[41m!!!!!!\x1B[0m");
			debug = 0;
		}
		printf("%s\x1B[0m\"", pipe[i] + debug);
		if (pipe[i + 1])
			printf(", ");
	}
	if (nl)
		printf("]\n");
	else
		printf("]");
}

void	print_command(char ***pipes)
{
	int	i;

	if (pipes[1])
	{
		i = -1;
		printf("[\n");
		while (pipes[++i])
		{
			printf("\t");
			print_pipe(pipes[i], 0);
			if (pipes[i + 1])
				printf(",");
			printf("\n");
		}
		printf("]\n");
	}
	else if (pipes[0])
		print_pipe(pipes[0], 1);
	else
		printf("NULL\n");
}

char	*add_red(char *str, int i)
{
	return (ft_strjoin(ft_substr(str, 0, i),
			ft_strjoin("\x1B[31m",
				ft_strjoin(ft_substr(str, i, 1),
					ft_strjoin("\x1B[0m",
						ft_substr(str, i + 1, ft_strlen(str)))))));
}

void	print_cutting_index(int *cutting_index)
{
	int	i;

	i = -1;
	while (cutting_index[++i] != -1)
		printf("%d ", cutting_index[i]);
	printf("\n");
}
