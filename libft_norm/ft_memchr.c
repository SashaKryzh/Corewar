/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 09:07:26 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 09:07:27 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmps;
	unsigned char	tmpc;

	i = 0;
	tmps = (unsigned char *)s;
	tmpc = (unsigned char)c;
	while (i < n)
	{
		if (tmps[i] == tmpc)
			return ((void *)&tmps[i]);
		i++;
	}
	return (NULL);
}
