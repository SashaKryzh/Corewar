/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:25:43 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/23 13:25:43 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_size;
	size_t src_size;

	dst_size = 0;
	while (dst[dst_size] && dst_size < size)
		dst_size++;
	if (dst_size == size)
		return (ft_strlen(src) + size);
	i = dst_size;
	src_size = 0;
	while (src[src_size] && i < size - 1)
	{
		dst[i] = src[src_size];
		i++;
		src_size++;
	}
	dst[i] = '\0';
	return (i + ft_strlen(src) - src_size);
}
