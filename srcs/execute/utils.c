/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:19:53 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/19 19:13:21 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "minishell.h"

void	remove_cmd(char **pipes)
{
	int		i;

	i = 0;
	free(pipes[i]);
	while (pipes[i + 1])
	{
		pipes[i] = pipes[i + 1];
		i++;
	}
	pipes[i] = NULL;
}

int	remove_redirect(char **pipe, int i)
{
	if (i && pipe[i - 1][0] == '2')
		remove_cmd(pipe + i-- - 1);
	remove_cmd(pipe + i);
	if (pipe[i] && pipe[i][0] == '2')
		remove_cmd(pipe + i);
	if (pipe[i])
		remove_cmd(pipe + i--);
	return (i);
}

char	disable_pipe(t_pipe **tpipe, char **pipe)
{
	free(*pipe);
	*pipe = NULL;
	(*tpipe)->args = pipe;
	(*tpipe)->next = NULL;
	if (pipe_add_back(tpipe, pipe_new(0, 0, (*tpipe)->env)))
		return (1);
	*tpipe = (*tpipe)->next;
	return (0);
}

// char	*trad_heredoc(char *line, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;
// 	char	*temp2;

// 	i = -1;
// 	temp = malloc (sizeof (char) + ft_strlen(line));
// 	if (!temp)
// 		return (NULL);
// 	while (line[++i])
// 	{
// 		j = 0;
// 		if (line[i] == '$')
// 		{
// 			while (line[i + j] && line[j + i] != ' ')
// 				j++;
// 			temp2 = env_get_value(env, ft_substr);
// 		}
// 		else
// 			temp[i] = line [i];
// 	}
// 	free(line);
// 	return (temp);
// }


char	*trad_heredoc(char *line, char **env)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;

	temp = NULL;
	i = 0;
	printf ("=======\\\\\\\\\\\\\\=======\n");
	while (line[i])
	{
		j = i;
		while (line[i] && line[i] != '$')
			i++;          // i = $ / \0
		if (line[i] == '$')
		{
			temp = malloc (sizeof (char) * i);
			if (!temp)
				return (0);
			j = i + 1;  // j = $+1
			temp[i-1] = 0;
			i--;
			while (i--)
			{
				printf("i = %d\n", i);
				temp[i] = line [i];
			}
			printf ("test out of loop \n");
			i = j - 1;  // i = $
			while (!line[j] && line[j] != ' ')
				j++;     // j = ' ' / \0
			temp2 = ft_substr(line, i + 1, j - 1);
			printf("name = '%s'\n", temp2);
			printf ("==============\n");
			printf("temp2 = %s\n", env_get_value(env, temp2));
			printf("temp = %s\n", temp);
			temp = ft_strjoin_free(temp, env_get_value(env, temp2), FREE_BOTH);
			printf("join = %s\n", temp);
			free(temp2);
			i += j;     //  i = ' ' / \0
		}
	}
	if (!temp)
		temp = ft_strdup(line);
	printf("temp = %s\n", temp);
	printf ("=======\\\\\\\\\\\\\\=======\n");
	free(line);
	return (temp);
}
