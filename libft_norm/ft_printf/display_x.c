/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 08:51:00 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/15 08:51:01 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*x_alter(t_pf_arg *arg, char *s, int len)
{
	char	*tmp;
	int		i;

	MALCH((tmp = ft_strnew(len + 2)));
	i = 0;
	while (i < len)
	{
		tmp[i + 2] = s[i];
		i++;
	}
	tmp[0] = '0';
	tmp[1] = 'X';
	free(s);
	arg->alter = 0;
	return (tmp);
}

char		*x_precision(t_pf_arg *arg, char *s)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (arg->precision < len)
	{
		if (arg->alter && arg->precision != -1)
			s = x_alter(arg, s, len);
		return (s);
	}
	if (arg->precision == -1)
		return (s);
	MALCH((tmp = ft_strnew(arg->precision)));
	i = 0;
	while (i < arg->precision - len)
		tmp[i++] = '0';
	ft_strcpy(&tmp[i], s);
	if (arg->alter)
		tmp = x_alter(arg, tmp, arg->precision);
	return (tmp);
}

int			x_pf_padding(t_pf_arg *arg, char pad, int i)
{
	int ret;

	ret = 0;
	if (arg->alter)
		ret = 2;
	if (arg->alter && arg->zero_pad)
		ft_putstr("0x");
	arg->alter = arg->zero_pad ? 0 : arg->alter;
	i += ret;
	while (i++ < arg->width && !arg->left_adj)
	{
		write(1, &pad, 1);
		ret++;
	}
	if (arg->alter)
		ft_putstr("0x");
	arg->alter = 0;
	return (ret);
}

int			pf_display_x(t_pf_arg *arg, va_list ap, char spec)
{
	uintmax_t	n;
	char		*s;
	int			ret;

	n = pf_get_unsigned(arg, ap);
	MALCH((s = pf_u_itoa_base(n, 16)));
	*s = arg->precision == 0 && n == 0 ? '\0' : *s;
	arg->alter = n == 0 ? 0 : arg->alter;
	s = x_precision(arg, s);
	ret = ft_strlen(s);
	if (arg->width > ret)
		ret += x_pf_padding(arg, arg->pad, ret);
	ret += arg->alter ? 2 : 0;
	s = arg->alter ? x_alter(arg, s, ret) : s;
	if (spec == 'x')
		pf_to_lowercase(s);
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += pf_padding(arg, ' ', ret);
	free(s);
	return (ret);
}
