/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:02:56 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 10:02:57 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = i;
		k = 0;
		while (haystack[j] == needle[k] && j < len)
		{
			if (needle[k + 1] == '\0')
				return ((char *)&haystack[i]);
			k++;
			j++;
		}
		i++;
	}
	return (NULL);
}
