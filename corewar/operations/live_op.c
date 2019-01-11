/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:40:20 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 14:40:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		live_op(uint8_t *arena, t_car *car)
{
	int arg;

	car->last_live = g_cnt_cycles;
	arg = get_dir(arena, car, (car->position + 1) % MEM_SIZE);
	// ft_printf("%d\n", arg);
	if (ft_abs(arg) != 0 && ft_abs(arg) <= MAX_PLAYERS)
		g_players[ft_abs(arg) - 1].alive = 1;
}
