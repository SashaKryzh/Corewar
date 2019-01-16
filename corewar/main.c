/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 07:54:25 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 07:54:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

t_player	g_players[MAX_PLAYERS + 1];
t_car		*g_carriage;

int			g_last_alive;
int			g_cnt_cars;

int			g_cycles_to_die = CYCLE_TO_DIE;

int			g_cnt_live;
int			g_cnt_cycles;
int			g_cnt_checks;

void		exit_func(char *msg)
{
	ft_printf("[Error]: %s\n", msg);
	exit(0);
}

void		get_op_code(t_car *car, uint8_t op)
{
	car->op = op;
	if (op >= 0x01 && op <= 0x10)
		car->remain_cycles = g_op[op - 1].to_wait;
}

void		manage_op(t_cell *arena, t_car *car)
{
	if (g_op[car->op - 1].is_args_types)
	{	
		if (get_op_data(arena, car))
			(*g_opers[car->op])(arena, car);
		else
		{
			putfile_hex(MEM_SIZE, arena, 1, 32); //
			ft_printf("%d\n", g_cnt_cycles);
		}
	}
	else
		(*g_opers[car->op])(arena, car);
	skip_op(arena, car);
	ft_printf("\n");
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
					ft_printf("%s (cycle: %d, pos : %d):\n", g_op[tmp->op - 1].name, g_cnt_cycles, tmp->position);
					manage_op(arena, tmp);
				}
				else
				{
					ft_printf("not supported %s (%d):\n", g_op[tmp->op - 1].name, g_cnt_cycles);
					exit(1);
					tmp->position = (tmp->position + 1) % MEM_SIZE;
				}
			}
			tmp = tmp->next;
		}
		check_battle(car);
		if (g_cnt_cycles == g_dump)
		{
			putfile_hex(MEM_SIZE, arena, 1, 32); //
			exit(1);
		}
	}
}

void		check_battle(t_car *car)
{
	static int	prev_cycles_to_die;

	g_cnt_cycles++;
	if (!prev_cycles_to_die)
		prev_cycles_to_die = g_cycles_to_die;
	if (g_cnt_cycles % g_cycles_to_die == 0 || g_cycles_to_die <= 0)
	{
		g_cnt_checks++;
		check_cars(g_carriage);
		if (g_cnt_live >= NBR_LIVE)
		{
			g_cycles_to_die -= CYCLE_DELTA;
			g_cnt_checks = 0;
		}
		if (g_cnt_checks == MAX_CHECKS)
		{
			if (prev_cycles_to_die == g_cycles_to_die && g_cycles_to_die > 0)
			{
				g_cycles_to_die -= CYCLE_DELTA;
				prev_cycles_to_die = g_cycles_to_die;
			}
			g_cnt_checks = 0;
		}
		g_cnt_live = 0;
	}
}

void		check_cars(t_car *car)
{
	t_car *tmp;

	tmp = car;
	while (tmp)
	{
		if (g_cnt_cycles - tmp->last_live >= g_cycles_to_die)
		{
			ft_printf("car is dead\n");
			delete_t_car(tmp);
		}
		tmp = tmp->next;
	}
	if (!g_carriage)
	{
		ft_printf("The winer is %s", g_players[g_last_alive - 1].name);
	}
}

int			main(int ac, char *av[])
{
	t_cell			*arena;

	g_last_alive = parse_players(g_players, ac, av);
	g_cnt_cars = g_last_alive;
	// ft_printf("last alive: %d, visu: %d, dump: %d\n", g_last_alive, g_visual, g_dump); //
	arena = init_battlefield(g_players);
	g_carriage = init_cars();

	print_players(g_players); //
	ft_printf("\nCNT: %d\n", g_last_alive); //
	putfile_hex(MEM_SIZE, arena, 1, 32); //
	print_cars(g_carriage); //

	ft_printf("cnt cars: %d\n", g_cnt_cars);
	ft_printf("\n");
	battle(arena, g_carriage);
	return (0);
}
