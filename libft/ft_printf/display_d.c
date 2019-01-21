/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:37:07 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/12 12:37:09 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pf_d_pref(t_pf_arg *arg, char *s, int start)
{
	char	*tmp;

	MALCH((tmp = ft_strnew(ft_strlen(s) + 1)));
	ft_strcpy(&tmp[1], &s[start]);
	tmp[0] = arg->pref;
	arg->sign = 0;
	arg->blank = 0;
	arg->pref = '\0';
	free(s);
	return (tmp);
}

char		*d_precision(t_pf_arg *arg, char *s)
{
	char	*tmp;
	int		i;

	if (arg->precision < arg->nlen)
	{
		if (*s == '-')
		{
			MALCH((tmp = ft_strsub(s, 1, arg->nlen)));
			free(s);
			s = tmp;
		}
		if ((arg->blank || arg->pref) && (!arg->zero_pad || !arg->width))
			s = pf_d_pref(arg, s, ft_strlen(s) - arg->nlen);
		return (s);
	}
	i = 0;
	MALCH((tmp = ft_strnew(arg->precision)));
	while (i < arg->precision - arg->nlen)
		tmp[i++] = '0';
	ft_strcpy(&tmp[i], &s[ft_strlen(s) - arg->nlen]);
	free(s);
	if (arg->blank || arg->pref == '+' || arg->pref == '-')
		tmp = pf_d_pref(arg, tmp, 0);
	return (tmp);
}

int			pf_display_d(t_pf_arg *arg, va_list ap)
{
	intmax_t	n;
	char		*s;
	int			ret;

	n = pf_get_signed(arg, ap);
	MALCH((s = ft_itoa_base(n, 10)));
	arg->nlen = ft_nbrlen(n, 10);
	*s = arg->precision == 0 && n == 0 ? '\0' : *s;
	arg->pref = arg->sign ? '+' : arg->pref;
	arg->pref = n < 0 ? '-' : arg->pref;
	s = d_precision(arg, s);
	ret = ft_strlen(s);
	if (!arg->left_adj)
		ret += pf_padding(arg, arg->pad, ret);
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += pf_padding(arg, ' ', ret);
	free(s);
	return (ret);
}
