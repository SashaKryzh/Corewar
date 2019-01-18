/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:12:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/14 19:12:30 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pf_unsigned_precision(char *s, int prec)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (prec < len)
		return (s);
	tmp = ft_strnew(prec);
	i = 0;
	while (i < prec - len)
	{
		tmp[i] = '0';
		i++;
	}
	ft_strcpy(&tmp[i], s);
	free(s);
	return (tmp);
}

int			pf_padding(t_pf_arg *arg, char pad, int ret)
{
	char	s[arg->width - ret > 0 ? arg->width - ret : 1];
	int		i;

	if (arg->width - ret <= 0)
	{
		if (arg->pref)
			write(1, &arg->pref, 1);
		return (arg->pref ? 1 : 0);
	}
	i = 0;
	if (arg->pref)
		s[i++] = arg->pref;
	while (i < arg->width - ret)
		s[i++] = pad;
	write(1, s, arg->width - ret);
	return (i);
}

void		pf_to_lowercase(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}
