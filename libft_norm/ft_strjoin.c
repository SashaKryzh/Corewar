/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:41:31 by pzakala           #+#    #+#             */
/*   Updated: 2018/11/02 12:21:31 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char *s)
{
	char	*copy;
	int		n;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	n = ft_strlen(s);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (NULL);
	while (i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*new_str;
	int		i;

	if (s1 == NULL)
		return (ft_copy((char *)s2));
	if (s2 == NULL)
		return (ft_copy((char *)s1));
	len = ft_strlen((char *)s2) + ft_strlen((char *)s1) + 1;
	new_str = (char *)malloc(sizeof(char) * len);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		new_str[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		new_str[i++] = *s2;
		s2++;
	}
	new_str[i] = '\0';
	return (new_str);
}
