/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:20:26 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/12 16:26:13 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

static int	ft_length(char const *s1, char const *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s1[i])
	{
		i++;
		ret++;
	}
	i = 0;
	while (s2[i])
	{
		i++;
		ret++;
	}
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		ret_i;
	char	*ret;
	int		length;

	length = ft_length(s1, s2);
	ret = (char *)malloc((length + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret_i = 0;
	while (s1[ret_i])
	{
		ret[ret_i] = s1[ret_i];
		ret_i++;
	}
	i = 0;
	while (s2[i])
	{
		ret[ret_i] = s2[i];
		i++;
		ret_i++;
	}
	ret[ret_i] = '\0';
	return (ret);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void ft_free_2arr(char **arr)
{
	int i = 0;
	if(arr != NULL)
	{
		while(arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}