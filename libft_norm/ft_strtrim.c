/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:16:16 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 11:16:17 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	start = i;
	if (s[start] == '\0')
		return (ft_strnew(0));
	while (s[i])
	{
		if (ft_isprint((int)s[i]) && s[i] != ' ')
			end = i;
		i++;
	}
	res = ft_strsub(s, start, end - start + 1);
	return (res);
}
