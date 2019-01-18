/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:33:27 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/11 14:33:28 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize(t_pf_arg *arg)
{
	ft_bzero(arg, sizeof(t_pf_arg));
	arg->precision = -1;
}

static int	print_pf_arg(t_pf_arg *arg, char spec, va_list ap)
{
	if (spec == 'c' || spec == '%')
		return (pf_display_c(arg, ap, spec == '%' ? 1 : 0));
	if (spec == 's')
		return (pf_display_s(arg, ap));
	if (spec == 'd' || spec == 'i')
		return (pf_display_d(arg, ap));
	if (spec == 'u')
		return (pf_display_u(arg, ap));
	if (spec == 'o')
		return (pf_display_o(arg, ap));
	if (spec == 'x' || spec == 'X')
		return (pf_display_x(arg, ap, spec));
	if (spec == 'p')
		return (pf_display_p(arg, ap));
	if (spec == 'f')
		return (pf_display_f(arg, ap));
	if (spec == 'b')
		return (pf_display_b(arg, ap));
	return (-1);
}

static int	assemble_arg(char **format, va_list ap)
{
	int			ret;
	t_pf_arg	arg;

	initialize(&arg);
	pf_get_flags(&arg, format);
	pf_get_width(&arg, format, ap);
	pf_get_precision(&arg, format, ap);
	pf_get_lenght(&arg, format);
	arg.zero_pad = arg.precision >= 0 && **format != 'f'
	&& **format != 'c' && **format != 's' && **format != '%'
	? 0 : arg.zero_pad;
	arg.zero_pad = arg.left_adj ? 0 : arg.zero_pad;
	arg.pad = arg.zero_pad ? '0' : ' ';
	arg.blank = arg.sign ? 0 : arg.blank;
	if ((ret = print_pf_arg(&arg, **format, ap)) == -1)
		return (0);
	*format += 1;
	return (ret);
}

static int	print(char *format, va_list ap)
{
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = format;
	while (*format)
	{
		if (*format == '%')
		{
			write(1, tmp, (size_t)(format - tmp));
			format++;
			ret += assemble_arg(&format, ap);
			tmp = format;
			continue ;
		}
		format++;
		ret++;
	}
	write(1, tmp, (size_t)(format - tmp));
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = print((char *)format, ap);
	va_end(ap);
	return (ret);
}
