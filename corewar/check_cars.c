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

t_car		*delete_t_car(t_car *to_del)
{
	t_car *tmp;

	if (g_carriage == to_del)
	{
		g_carriage = to_del->next;
		free(to_del);
		return (g_carriage);
	}
	tmp = g_carriage;
	while (tmp->next && tmp->next != to_del)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	free(to_del);
	return (tmp->next);
}

void		check_cars(void)
{
	t_car *tmp;

	tmp = g_carriage;
	while (tmp)
	{
		if (g_cnt_cycles - tmp->last_live >= g_cycles_to_die)
			tmp = delete_t_car(tmp);
		else
			tmp = tmp->next;
	}
}
