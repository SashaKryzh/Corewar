/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:02:58 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 17:14:13 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		manage_op(t_cell *arena, t_car *car)
{
	if (g_op[car->op - 1].is_args_types)
	{
		if (get_op_data(arena, car))
			(*g_opers[car->op])(arena, car);
	}
	else
		(*g_opers[car->op])(arena, car);
	skip_op(car);
}

void		battle(t_cell *arena)
{
	t_car	*tmp;

	while (1)
	{
		tmp = g_carriage;
		if (SHOW_CYCLES && g_cnt_cycles >= g_start_to_show)
			ft_printf("It is now cycle %d\n", g_cnt_cycles);
		while (tmp)
		{
			if (!tmp->remain_cycles)
				get_op_code(tmp, arena[tmp->position].v);
			tmp->remain_cycles -= tmp->remain_cycles > 0 ? 1 : 0;
			if (!tmp->remain_cycles)
			{
				if (tmp->op >= 0x01 && tmp->op <= 0x10)
					manage_op(arena, tmp);
				else
					tmp->position = (tmp->position + 1) % MEM_SIZE;
			}
			tmp = tmp->next;
		}
		check_battle_status(arena);
	}
}

void		check_battle_status(t_cell *arena)
{
	check_battle();
	if (g_cnt_cycles == g_dump)
		putarena(arena);
	if (g_visual)
		update_view(arena);
	g_cnt_cycles++;
}

void		check_battle(void)
{
	static int	cnt_checks;
	static int	cnt_cycles;
	static int	prev_to_die;
	static int	changed;

	cnt_cycles++;
	prev_to_die = !prev_to_die ? g_cycles_to_die : prev_to_die;
	if (cnt_cycles % g_cycles_to_die == 0 || g_cycles_to_die <= 0)
	{
		cnt_checks++;
		check_cars();
		if (g_cnt_live >= NBR_LIVE && (changed = 1))
		{
			g_cycles_to_die -= CYCLE_DELTA;
			prev_to_die = g_cycles_to_die;
			cnt_checks = 0;
		}
		if (cnt_checks != 0 && !(cnt_checks %= MAX_CHECKS) && (changed = 1))
			if (prev_to_die == g_cycles_to_die && g_cycles_to_die > 0)
			{
				g_cycles_to_die -= CYCLE_DELTA;
				prev_to_die = g_cycles_to_die;
			}
		check_battle_2(&cnt_cycles, &changed);
	}
}

void		check_battle_2(int *cnt_cycles, int *changed)
{
	g_cnt_live = 0;
	*cnt_cycles = 0;
	*changed -= 1;
	if (SHOW_CYCLES && *changed == 0)
		ft_printf("Cycle to die is now %d\n", g_cycles_to_die);
	is_winner();
}
