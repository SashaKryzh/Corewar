/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_t_car.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:34:02 by pzakala           #+#    #+#             */
/*   Updated: 2019/01/16 15:34:07 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

t_car 	*delete_t_car(t_car *to_del)
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
