/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:01:28 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/23 12:01:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (i == n)
		return (dest);
	else if (!src[i] && i < n)
	{
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
		return (dest);
	}
	dest[i] = '\0';
	return (dest);
}
