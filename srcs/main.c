/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/07/03 10:31:31 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_shel	data;

	(void)argc;
	(void)argv;
	init_shell(env);
	while (1)
	{
		line = readline(PROMT);
		if (line == NULL)
			return (0);
		printf("line = %s\n", line);
		split_mini(line, &data);
		free(line);
		printf ("data.cmd[0].cmd == %s\n", data.cmd[0].cmd);
		if (ft_strncmp (data.cmd[0].cmd, "exit", 4) == 0)
		{
			ft_clear_data(&data);
			return (0);
		}
		ft_clear_data(&data);
	}
	return (0);
}
