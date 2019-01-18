/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 21:54:06 by pzakala           #+#    #+#             */
/*   Updated: 2018/11/05 16:18:55 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nextchr(const char *str, char c, size_t r)
{
	size_t i;

	i = 0;
	while (i < r)
	{
		if (*str == c)
		{
			return (i);
		}
		str++;
		i++;
	}
	return (r);
}

char			**ft_strcut(const char *str, char c, size_t r)
{
	char	**l;
	size_t	j;
	size_t	i;
	size_t	n;

	if (str == NULL)
		return (NULL);
	j = 0;
	i = 0;
	l = (char **)malloc(3 * sizeof(char *));
	if (l == NULL)
		return (NULL);
	l[2] = NULL;
	n = ft_nextchr(str, c, r);
	l[0] = (char *)malloc(sizeof(char) * (n + 1));
	l[1] = (char *)malloc(sizeof(char) * (r - n + 1));
	while (j < n)
		*(l[0] + i++) = *(str + j++);
	l[0][i] = '\0';
	i = 0;
	j++;
	while (j < r)
		*(l[1] + i++) = *(str + j++);
	l[1][i] = '\0';
	return (l);
}
