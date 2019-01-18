/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:40:28 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/11 16:40:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_match(char *s1, char *s2)
{
	if (*s1 && *s2 == '*')
		return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	else if (!(*s1) && *s2 == '*')
		return (ft_match(s1, s2 + 1));
	else if (*s1 && *s2 && *s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	else if (!(*s1) && !(*s2))
		return (1);
	return (0);
}
