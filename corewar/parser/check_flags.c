/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 09:40:10 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 09:40:10 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

static void		check_dump(int ac, char *av[], int *i)
{
	if (*i + 1 >= ac || g_dump >= 0)
		exit_func("-dump error");
	*i += 2;
	if ((g_dump = ft_atoi(av[*i - 1])) < 0)
		exit_func("-dump error");
}

static void		check_v(int ac, char *av[], int *i)
{
	if (*i + 1 >= ac)
		exit_func("-v error");
	*i += 2;
	g_debug |= ft_atoi(av[*i - 1]);
}

int				check_flags(int ac, char *av[], int *i)
{
	if (ft_strequ(av[*i], "-dump"))
	{
		check_dump(ac, av, i);
		return (*i >= ac ? 0 : check_flags(ac, av, i));
	}
	else if (ft_strequ(av[*i], "-nc"))
	{
		g_visual = 1;
		*i += 1;
		return (*i >= ac ? 0 : check_flags(ac, av, i));
	}
	else if (ft_strequ(av[*i], "-v"))
	{
		check_v(ac, av, i);
		return (*i >= ac ? 0 : check_flags(ac, av, i));
	}
	else if (ft_strequ(av[*i], "-f64"))
	{
		g_format = 64;
		*i += 1;
		return (*i >= ac ? 0 : check_flags(ac, av, i));
	}
	return (1);
}

void			check_flags_priority(void)
{
	if (g_visual)
	{
		g_debug = 0;
		g_dump = -1;
	}
	if (g_debug)
	{
		g_format = 64;
	}
}
