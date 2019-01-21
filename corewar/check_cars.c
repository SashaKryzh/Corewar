/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 08:18:57 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 08:18:57 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

t_car		*delete_t_car(t_car *prev, t_car *to_del)
{
	if (g_carriage == to_del)
	{
		g_carriage = to_del->next;
		free(to_del);
		return (g_carriage);
	}
	prev->next = to_del->next;
	free(to_del);
	return (prev->next);
}

void		check_cars(void)
{
	t_car *prev;
	t_car *cur;

	prev = NULL;
	cur = g_carriage;
	while (cur)
	{
		if (g_cnt_cycles - cur->last_live >= g_cycles_to_die)
			cur = delete_t_car(prev, cur);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
