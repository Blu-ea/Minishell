/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:41:27 by amiguez           #+#    #+#             */
/*   Updated: 2023/01/21 16:00:39 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		write (2, PROMT_E, ft_strlen(PROMT_E));
		write (2, " pwd: Failed", 13);
		return (EXIT_FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
