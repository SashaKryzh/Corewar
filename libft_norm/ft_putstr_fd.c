/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:38:11 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/23 10:38:12 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_fd(char const *s, int fd)
{
	size_t len;

	if (!s)
		return (0);
	if ((len = ft_strlen(s)))
		write(fd, s, len);
	return (len);
}
