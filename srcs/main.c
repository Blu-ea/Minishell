/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:49:08 by amiguez           #+#    #+#             */
/*   Updated: 2022/06/10 17:13:29 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	char	**args;
	int		status;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
			return (0);
		ft_printf("line = %s\n", line);
		free(line);
	}
	return (0);
}
