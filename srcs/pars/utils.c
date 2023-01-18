/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:06:19 by jcollon           #+#    #+#             */
/*   Updated: 2023/01/18 14:47:00 by jcollon          ###   ########lyon.fr   */
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
		ft_exit("malloc failed", 1);
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
