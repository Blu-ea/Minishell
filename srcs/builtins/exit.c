/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:07:09 by amiguez           #+#    #+#             */
/*   Updated: 2022/10/06 06:57:09 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Do Nothing if on a pipe

	don t exit if arg[0] ->int && more that 1 arg

	exit if arg[0] -> char*  $? 255
	exit if none arg		$? 0
	print "exit" if exit
*/
int		bin_exit(char **args)
{
	int		i;
	int		ret;
	char	*cmp;

	i = 0;
	if (!*args)
	{
		printf("exit\n");
		exit(0);
	}
	ret = 0;
	ret = ft_atoi(args[i]);
	cmp = ft_itoa(ret);
	if (ft_strncmp(cmp, args[0], ft_strlen(args[0])) != 0 )
	{
		printf("exit\n%s exit: %s: Numeric argument required\n", PROMT_E, args[0]);
		exit(255);
	}
	while (args[i])
		i++;
	if (i >= 2)
	{
		printf("%s exit: too many arguments\n", PROMT_E);
		return (1);
	}
	printf("exit\n");
	exit(ret % 256);
}
