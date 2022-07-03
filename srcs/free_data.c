/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:08:04 by amiguez           #+#    #+#             */
/*   Updated: 2022/07/03 10:12:01 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief is there to cleat data between two call
 * 
 * @param data 
 */
void	ft_clear_data(t_shel *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		free(data->cmd[i].cmd);
		ft_free_2d_array(data->cmd[i].args);
		i++;
	}
	free(data->cmd);
	data->nb_cmd = 0;
}
