/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:33:06 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/11 14:33:07 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_pf_arg
{
	int		alter;
	int		zero_pad;
	char	pad;
	int		left_adj;
	int		sign;
	int		blank;
	char	pref;
	int		width;
	int		precision;
	int		nlen;
	enum	e_pf_length
	{
		no_lenght = 0,
		hh,
		h,
		l,
		ll,
		j,
		z,
		L
	}		pf_length;
}				t_pf_arg;

int				ft_printf(const char *format, ...);

/*
** Parser
*/

void			pf_get_flags(t_pf_arg *arg, char **format);
void			pf_get_width(t_pf_arg *arg, char **format, va_list ap);
void			pf_get_precision(t_pf_arg *arg, char **format, va_list ap);
void			pf_get_lenght(t_pf_arg *arg, char **format);

/*
** Display
*/

int				pf_display_d(t_pf_arg *arg, va_list ap);
int				pf_display_c(t_pf_arg *arg, va_list ap, int percent);
int				pf_display_s(t_pf_arg *arg, va_list ap);
int				pf_display_o(t_pf_arg *arg, va_list ap);
int				pf_display_u(t_pf_arg *arg, va_list ap);
int				pf_display_x(t_pf_arg *arg, va_list ap, char spec);
int				pf_display_p(t_pf_arg *arg, va_list ap);
int				pf_display_f(t_pf_arg *arg, va_list ap);
int				pf_display_b(t_pf_arg *arg, va_list ap);

/*
** Get value
*/

uintmax_t		pf_get_unsigned(t_pf_arg *arg, va_list ap);
intmax_t		pf_get_signed(t_pf_arg *arg, va_list ap);

int				pf_padding(t_pf_arg *arg, char pad, int ret);
char			*pf_d_pref(t_pf_arg *arg, char *s, int start);
void			pf_to_lowercase(char *s);

char			*pf_u_itoa_base(uintmax_t nbr, int base);
char			*pf_dtoa(long double n, int after);

char			*pf_unsigned_precision(char *s, int prec);

#endif
