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

t_player	*g_players;
t_car		*g_carriage;

int			g_last_alive;
int			g_cnt_cars;

int			g_cnt_cycles;
int			g_cnt_live;
int			g_cnt_checks;

int			g_cycles_to_die = CYCLE_TO_DIE;

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

void		execute_op(uint8_t *arena, t_car *car)
{
	if (car->op == 0x01)
		live_op(arena, car);
	else if (car->op == 0x02)
		ld_op(arena, car);
	else if (car->op == 0x04)
		add_sub_op(arena, car);
	else if (car->op == 0x09)
		zjmp_op(arena, car);
	else if (car->op == 0x0A)
		ldi_op(arena, car);
	else if (car->op == 0x0B)
		sti_op(arena, car);
	else if (car->op == 0x0C || car->op == 0x0F)
		fork_op(arena, car);
	else if (car->op == 0x10)
		aff_op(arena, car);
	else
		ft_printf("Nea...\n");
}

void		add_sub_op(uint8_t *arena, t_car *car)
{
	int reg_nums[3];
	int	to_put;
	int i;

	i = 0;
	while (i < 3)
	{
		reg_nums[i] = get_reg_num(arena, car, i + 1);
		i++;
	}
	if (car->op == 0x04)
		to_put = car->regs[reg_nums[0] - 1] + car->regs[reg_nums[1] - 1];
	else
		to_put = car->regs[reg_nums[0] - 1] - car->regs[reg_nums[1] - 1];
	car->regs[reg_nums[2] - 1] = to_put;
	car->carry = to_put == 0 ? 1 : 0;
}

void		manage_op(uint8_t *arena, t_car *car)
{
	if (g_op[car->op - 1].is_args_types)
	{	
		if (get_op_data(arena, car))
			execute_op(arena, car);
		else
		{
			putfile_hex(MEM_SIZE, arena, 1, 32); //
			ft_printf("%d\n", g_cnt_cycles);
		}
	}
	else
		execute_op(arena, car);
	skip_op(arena, car);
	ft_printf("\n");
}

void		battle(uint8_t *arena, t_car *car)
{
	t_car	*tmp;

	while (1)
	{
		tmp = g_carriage;
		while (tmp)
		{
			if (!tmp->remain_cycles)
			{
				get_op_code(tmp, arena[tmp->position]);
				// putbyte_hex(tmp->op);
			}
			tmp->remain_cycles = tmp->remain_cycles > 0 ? tmp->remain_cycles - 1 : tmp->remain_cycles;
			if (!tmp->remain_cycles)
			{
				if (tmp->op == 0x01 || tmp->op == 0x02 || tmp->op == 0x04 || tmp->op == 0x09 || tmp->op == 0x0A || tmp->op == 0x0B || tmp->op == 0x0C || tmp->op == 0x0F || tmp->op == 0x10)
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
		// if (g_cnt_cycles == 25)
		// {
		// 	putfile_hex(MEM_SIZE, arena, 1, 32); //
		// 	exit(1);
		// }
	}
}

void		check_battle(t_car *car)
{
	static int	prev_cycles_to_die;

	g_cnt_cycles++;
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
			if (prev_cycles_to_die == g_cycles_to_die)
				g_cycles_to_die -= CYCLE_DELTA;
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
			exit(0);
		}
		tmp = tmp->next;
	}
}

int			main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];
	t_car			*carriage;
	uint8_t			*arena;

	g_last_alive = parse_players(champs, ac, av);
	arena = init_battlefield(champs);
	carriage = init_cars();

	print_players(champs); //
	ft_printf("\nCNT: %d\n", g_last_alive); //
	putfile_hex(MEM_SIZE, arena, 1, 32); //
	print_cars(carriage); //

	g_carriage = carriage;
	g_cnt_cars = g_last_alive;
	g_players = champs;
	ft_printf("cnt cars: %d\n", g_cnt_cars);
	ft_printf("\n");
	battle(arena, carriage);
	return (0);
}
