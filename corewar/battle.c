/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:02:58 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/17 17:23:54 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		manage_op(t_cell *arena, t_car *car)
{
	// if (g_cnt_cycles == g_dump - 1)
	// 	ft_printf("%d %02x\n", car->position, arena[car->position].v);
	if (g_op[car->op - 1].is_args_types)
	{
		if (get_op_data(arena, car))
			(*g_opers[car->op])(arena, car);
	}
	else
		(*g_opers[car->op])(arena, car);
	skip_op(arena, car);
}

void		battle(t_cell *arena, t_car *car)
{
	t_car	*tmp;

	while (1)
	{
		tmp = g_carriage;
		if (SHOW_CYCLES)
			ft_printf("It is now cycle %d\n", g_cnt_cycles);
		while (tmp)
		{
			if (!tmp->remain_cycles)
				get_op_code(tmp, arena[tmp->position].v);
			tmp->remain_cycles = tmp->remain_cycles > 0 ? tmp->remain_cycles - 1 : tmp->remain_cycles;
			if (!tmp->remain_cycles)
			{
				if (tmp->op >= 0x01 && tmp->op <= 0x10)
				{
					// ft_printf("%s (cycle: %d, pos : %d):\n", g_op[tmp->op - 1].name, g_cnt_cycles, tmp->position);
					manage_op(arena, tmp);
				}
				else
					tmp->position = (tmp->position + 1) % MEM_SIZE;
			}
			tmp = tmp->next;
		}
		if (!g_dump || g_cnt_cycles == g_dump)
		{
			putfile_hex(MEM_SIZE, arena, 1, 64); //
			exit(1);
		}
		check_battle(car);
		if (g_visual)
			update_view(arena);
	}
}

void		check_battle(t_car *car)
{
	static int	prev_to_die;
	static int	cnt_c;
	int			changed;

	cnt_c++;
	// ft_printf("cnt_c: %d, to_die: %d, cycle: %d\n", cnt_c, g_cycles_to_die, g_cnt_cycles);
	prev_to_die = !prev_to_die ? g_cycles_to_die : prev_to_die;
	if (cnt_c % g_cycles_to_die == 0 || g_cycles_to_die <= 0)
	{
		g_cnt_checks++;
		if (g_cnt_live >= NBR_LIVE)
		{
			g_cycles_to_die -= CYCLE_DELTA;
			prev_to_die = g_cycles_to_die;
			g_cnt_checks = 0;
			changed = 1;
		}
		if (g_cnt_checks == MAX_CHECKS)
		{
			if (prev_to_die == g_cycles_to_die && g_cycles_to_die > 0)
			{
				g_cycles_to_die -= CYCLE_DELTA;
				prev_to_die = g_cycles_to_die;
			}
			g_cnt_checks = 0;
			changed = 1;
		}
		g_cnt_live = 0;
		cnt_c = 0;
		if (SHOW_CYCLES && --changed == 0)
			ft_printf("Cycle to die is now %d\n", g_cycles_to_die);
		check_cars(g_carriage);
	}
	g_cnt_cycles++;
}

void		check_cars(t_car *car)
{
	t_car *tmp;

	tmp = car;
	while (tmp)
	{
		if (g_cnt_cycles - tmp->last_live >= g_cycles_to_die)
			delete_t_car(tmp);
		tmp = tmp ? tmp->next : NULL;
	}
	if (!g_carriage)
	{
		ft_printf("Contestant %d, \"%s\", has won ! (%d)\n", g_last_alive, g_players[g_last_alive - 1].name, g_cnt_cycles);
		exit(1);
	}
}
