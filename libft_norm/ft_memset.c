/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 08:17:19 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 08:17:19 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	ctmp;

	i = 0;
	tmp = (unsigned char *)b;
	ctmp = (unsigned char)c;
	while (i < len)
	{
		tmp[i] = ctmp;
		i++;
	}
	return (b);
}
