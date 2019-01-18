/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:34:15 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/16 13:34:15 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strrev(char *s)
{
	char	c;
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		c = s[len - i - 1];
		s[len - i - 1] = s[i];
		s[i] = c;
		i++;
	}
}
