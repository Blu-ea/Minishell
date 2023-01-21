/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:27 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 23:34:47 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_print_error("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
