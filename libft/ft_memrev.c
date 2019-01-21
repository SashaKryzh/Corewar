/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:18:42 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 15:18:42 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memrev(void *s, size_t len)
{
	size_t	i;
	char	*tmpmem;
	char	tmp;

	i = 0;
	tmpmem = (char *)s;
	while (i < len / 2)
	{
		tmp = tmpmem[i];
		tmpmem[i] = tmpmem[len - i - 1];
		tmpmem[len - i - 1] = tmp;
		i++;
	}
}
