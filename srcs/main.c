/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/06/15 06:37:57 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	int		status;

	(void)argc;
	(void)argv;
	init_shell(env);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
			return (0);
		args = split_cmd(line);
		execve(args[0], args, env);
		ft_printf("line = %s\n", line);
		free(line);
	}
	return (0);
}
