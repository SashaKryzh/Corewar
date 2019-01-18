/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 08:43:20 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 08:43:21 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*tmpdst;
	char	*tmpsrc;

	tmpdst = (char *)dst;
	tmpsrc = (char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			tmpdst[len - 1] = tmpsrc[len - 1];
			len--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			tmpdst[i] = tmpsrc[i];
			i++;
		}
	}
	return (dst);
}
