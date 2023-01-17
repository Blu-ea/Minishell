/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:06:19 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/16 19:14:54 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Join all three strings and free s1 and s3
 * 
 * @param s1: First string will be freed
 * @param s2: Second string will not be freed
 * @param s3: Third string will be freed
 * @return s1 + s2 + s3
 */
char	*ft_join3(char *s1, const char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	free(s3);
	return (ret);
}

char	*add_prefix(const char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s2);
	return (ret);
}

int	ft_inttablen(int *tan)
{
	int	i;

	i = 0;
	while (tan[i] != -1)
		i++;
	return (i);
}

int	*append_int(int *tab, int nb)
{
	int	*ret;
	int	i;

	i = 0;
	ret = malloc(sizeof(int) * (ft_inttablen(tab) + 2));
	while (tab[i] != -1)
	{
		ret[i] = tab[i];
		i++;
	}
	ret[i] = nb;
	ret[i + 1] = -1;
	free(tab);
	return (ret);
}

char	**insert(char **tab, char *str, int pos)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(*ret) * (ft_tablen(tab) + 2));
	if (!ret)
		ft_exit("malloc failed");
	while (tab[i] != NULL)
	{
		if (i == pos)
		{
			ret[i] = str;
			j++;
		}
		ret[i + j] = tab[i];
		i++;
	}
	ret[i + j] = NULL;
	free(tab);
	return (ret);
}

int	size_pipe(char **pipe, int index)
{
	int	i;
	int	j;

	j = 0;
	index++;
	while (--index)
	{
		while (pipe[j] && pipe[j][0] != '4')
			j++;
		j++;
	}
	i = 0;
	while (pipe[i + j] && pipe[i + j][0] != '4')
		i++;
	return (i);
}

int	split_merge_cmd(char ***pipe, int *indexs, int index,
	char **(*cut)(char *, int *))
{
	int		len;
	int		i;
	char	**tmp;

	if (indexs[0] == -1 || ft_inttablen(indexs) % 2 != 0)
		return (1);
	tmp = cut(pipe[0][index] + 1, indexs);
	len = ft_tablen(tmp);
	i = 0;
	while (tmp[i + 1])
	{
		*pipe = insert(*pipe, tmp[i], index + i);
		i++;
	}
	free(pipe[0][index + i]);
	pipe[0][index + i] = tmp[i];
	free(tmp);
	return (len);
}
