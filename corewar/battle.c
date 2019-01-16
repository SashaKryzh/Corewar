/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:02:58 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/16 19:02:58 by okryzhan         ###   ########.fr       */
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
		else
		{
			// putfile_hex(MEM_SIZE, arena, 1, 32); //
			// ft_printf("%d\n", g_cnt_cycles);
		}
	}
	else
		(*g_opers[car->op])(arena, car);
	skip_op(arena, car);
	// ft_printf("\n");
}

void		battle(t_cell *arena, t_car *car)
{
	t_car	*tmp;

	while (1)
	{
		tmp = g_carriage;
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
				{
					// ft_printf("not supported %s (%d):\n", g_op[tmp->op - 1].name, g_cnt_cycles);
					exit(1);
					tmp->position = (tmp->position + 1) % MEM_SIZE;
				}
			}
			tmp = tmp->next;
		}
		check_battle(car);
		if (g_visual)
			print_into_arena(arena, g_carriage);
		if (g_cnt_cycles == g_dump)
		{
			// putfile_hex(MEM_SIZE, arena, 1, 32); //
			exit(1);
		}
	}
}

void		check_battle(t_car *car)
{
	static int	prev_cycles_to_die;
	static int	cnt_c;

	g_cnt_cycles++;
	cnt_c++;
	// ft_printf("%d %d %d\n", cnt_c, g_cycles_to_die, g_cnt_cycles);
	if (!prev_cycles_to_die)
		prev_cycles_to_die = g_cycles_to_die;
	if (cnt_c % g_cycles_to_die == 0 || g_cycles_to_die <= 0)
	{
		g_cnt_checks++;
		check_cars(g_carriage);
		// ft_printf("cnt live: %d, cnt checks %d\n", g_cnt_live, g_cnt_checks);
		if (g_cnt_live >= NBR_LIVE)
		{
			g_cycles_to_die -= CYCLE_DELTA;
			prev_cycles_to_die = g_cycles_to_die;
			g_cnt_checks = 0;
		}
		if (g_cnt_checks == MAX_CHECKS)
		{
			// ft_printf("prev cycles %d\n", prev_cycles_to_die);
			if (prev_cycles_to_die == g_cycles_to_die && g_cycles_to_die > 0)
			{
				g_cycles_to_die -= CYCLE_DELTA;
				prev_cycles_to_die = g_cycles_to_die;
			}
			g_cnt_checks = 0;
		}
		g_cnt_live = 0;
		cnt_c = 0;
	}
	// if (g_cnt_cycles == 21563)
	// 	exit(0);
}

void		check_cars(t_car *car)
{
	t_car *tmp;

	tmp = car;
	while (tmp)
	{
		if (g_cnt_cycles - tmp->last_live >= g_cycles_to_die)
			delete_t_car(tmp);
		tmp = tmp->next;
	}
	if (!g_carriage)
	{
		ft_printf("Contestant %d, \"Batman\", has won !\n", g_last_alive, g_players[g_last_alive - 1]);
		exit(1);
	}
}
