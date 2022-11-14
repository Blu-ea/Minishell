/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:07:09 by amiguez           #+#    #+#             */
/*   Updated: 2022/11/14 06:28:15 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	/!\ Do Nothing if on a pipe /!\

	don t exit if arg[0] ->int && more that 1 arg

	exit if arg[0] -> char*  $? 255
	exit if none arg		$? 0
	print "exit" if exit
*/

int	exit_alpha(char *temp, char **arg);

int	bin_exit(char **arg)
{
	int		ret;
	char	*temp;

	if (arg == NULL || !*arg)
		printf("exit\n");
	if (arg == NULL || !*arg)
		exit(0);
	ret = ft_atoi(*arg);
	temp = ft_itoa(ret);
	if (ft_strncmp(temp, arg[0], ft_strlen(arg[0])) != 0)
		exit(exit_alpha(temp, arg));
	free(temp);
	temp = *arg;
	while (*arg)
		arg++;
	arg--;
	if (temp - *arg != 1 && temp - *arg != 0)
	{	
		printf("%s exit: too many arguments\n", PROMT_E);
		return (1);
	}
	printf("exit\n");
	ft_clear_line();
	exit(ret % 256);
}

int	exit_alpha(char *temp, char **arg)
{
	free(temp);
	printf("%s exit: %s: Numeric argument required\nexit\n", PROMT_E, *arg);
	ft_clear_line();
	return (255);
}