/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:12:24 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/18 14:42:51 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	print_pipe_struct(t_pipe *pipe)
{
	int	i;

	i = -1;
	if (pipe->fd[0] == -1)
		printf("\x1B[41m");
	else if (pipe->fd[0] != 0)
		printf("\x1B[32m");
	else
		printf("\x1B[2;34m");
	printf("%d\x1B[0m,", pipe->fd[0]);
	if (pipe->fd[1] == -1)
		printf("\x1B[41m");
	else if (pipe->fd[1] != 1)
		printf("\x1B[32m");
	else
		printf("\x1B[2;34m");
	printf("%d\x1B[0m", pipe->fd[1]);
	printf(" [");
	while (pipe->args[++i])
	{
		printf("\"%s\"", pipe->args[i]);
		if (pipe->args[i + 1])
			printf(", ");
	}
	printf("]");
	if (pipe->next && pipe->next->args)
	{
		printf("\x1B[32m next\x1B[0m ");
		printf("%s", pipe->next->args[0]);
	}
	else
		printf("\x1B[31m next\x1B[0m");
	printf("\n");
}

void	check_fd_leak(void)
{
	int		fd[10];

	fd[0] = open("/dev/null", O_RDONLY);
	fd[1] = open("/dev/null", O_RDONLY);
	fd[2] = open("/dev/null", O_RDONLY);
	fd[3] = open("/dev/null", O_RDONLY);
	fd[4] = open("/dev/null", O_RDONLY);
	fd[5] = open("/dev/null", O_RDONLY);
	fd[6] = open("/dev/null", O_RDONLY);
	fd[7] = open("/dev/null", O_RDONLY);
	fd[8] = open("/dev/null", O_RDONLY);
	fd[9] = open("/dev/null", O_RDONLY);
	printf("last fd = %d\n", fd[9] - 10);
	if (fd[9] != 12)
		printf("\x1B[41m!!!!!!!!!!!!!!!!!!fd leak!!!!!!!!!!!!!!!!!!\x1B[0m\n");
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	close(fd[4]);
	close(fd[5]);
	close(fd[6]);
	close(fd[7]);
	close(fd[8]);
	close(fd[9]);
}
