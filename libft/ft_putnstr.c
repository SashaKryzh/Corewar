/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:29:04 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/14 17:29:05 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnstr(char *s, size_t n)
{
	size_t len;

	len = 0;
	while (s[len] && len < n)
		len++;
	if (len)
		write(1, s, len);
	return (len);
}
