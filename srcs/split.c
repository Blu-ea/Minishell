/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:12:49 by jcollon           #+#    #+#             */
/*   Updated: 2022/07/03 10:38:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ft_split('|')
 * 
 * @param line 
 * @return char** 
 */
int	split_mini(char *line, t_shel *data)
{
	int		i;
	char	**temp;
	char	**temp_2;

	i = 0;
	data->nb_cmd = ft_count_pipe(line);
	if (data->nb_cmd == 0)
		return (EMPTY_LINE);
	data->cmd = malloc (sizeof(t_cmd) * data->nb_cmd + 1);
	if (data->cmd == NULL)
		return (1);//Need proper error handling
	data->cmd[data->nb_cmd].cmd = 0;
	temp = ft_split_quotes(line, '|');
	if (temp == NULL)
		return (1);//Need proper error handling
	while (i < data->nb_cmd)
	{
		temp_2 = ft_split_quotes(temp[i], ' ');
		data->cmd[i].cmd = ft_strdup (temp_2[0]);//Need proper error handling
		data->cmd[i].args = ft_tabdup (temp_2 + 1);//Need proper error handling
		i++;
		ft_free_2d_array(temp_2);
	}
	ft_free_2d_array(temp);
	return (0);
}

int	ft_count_pipe(char *line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 1;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
			line += ft_skip_quote(line);
		if (*line == '|')
			i++;
		line++;
	}
	return (i);
}
