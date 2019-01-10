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

int		g_last_alive;

int		g_cnt_cycles;
int		g_cnt_live;
int		g_cnt_checks;

int		g_cycles_to_die = CYCLE_TO_DIE;

void		exit_func(char *msg)
{
	ft_printf("[Error]: %s\n", msg);
	exit(0);
}

void		get_op_code(t_carriage *car, uint8_t op)
{
	car->op = op;
	if (op >= 0x01 && op <= 0x10)
		car->remain_cycles = g_op[op - 1].to_wait;
}

void		check_reg_num(uint8_t *arena, t_carriage *car, int reg_pos)
{
	uint8_t		byte;
	uint8_t		to_jump;
	uint8_t		i;
	uint8_t		j;
	int			reg_num;

	i = 6;
	j = 0;
	to_jump = 1;
	byte = arena[(car->position + 1) % MEM_SIZE];
	while (j < reg_pos)
	{
		if (((byte >> i) % 4) == REG_CODE) // checks fot active bit at needed position
		{
			to_jump += REG_SIZE;
		}
		else if (((byte >> i) % 4) == IND_CODE)
		{
			to_jump += IND_SIZE;
		}
		else if (((byte >> i) % 4) == DIR_CODE)
		{
			to_jump += g_op[car->op - 1].t_dir_size;
		}
		i -= 2;
		j++;
	}
	reg_num = arena[(car->position + 1 + to_jump) % MEM_SIZE];
	if (reg_num <= 0 || reg_num > REG_NUMBER)
		exit_func("Invalid REG NUMBER");
	ft_printf("reg num : %d\n", reg_num);
}

void		get_op_data(uint8_t *arena, t_carriage *car)
{
	uint8_t		byte;
	uint8_t		i;
	uint8_t		j;

	i = 6;
	j = 0;
	byte = arena[(car->position + 1) % MEM_SIZE];
	while (j < g_op[car->op - 1].args_num)
	{
		if (g_op[car->op - 1].args_types[j] >> ((byte >> i) % 4 - 1)) // checks fot active bit at needed position
		{
			if (((byte >> i) % 4) == IND_CODE)
			{
				ft_printf("T_IND\n");
				car->args_sizes[j] = IND_SIZE;
			}
			else if (((byte >> i) % 4) == DIR_CODE)
			{
				ft_printf("T_DIR\n");
				car->args_sizes[j] = g_op[car->op - 1].t_dir_size;
			}
			else
			{
				ft_printf("T_REG\n");
				car->args_sizes[j] = REG_SIZE;
				check_reg_num(arena, car, j);
			}
		}
		else
		{
			exit_func("Error in ARGS TYPES");
		}
		i -= 2;
		j++;
	}
}

void		execute_op(uint8_t *arena, t_carriage *car)
{
	if (g_op[car->op - 1].is_args_types)
		get_op_data(arena, car);
}

void		battle(uint8_t *arena, t_carriage *car)
{
	t_carriage	*tmp;

	tmp = car;
	while (tmp)
	{
		if (!tmp->remain_cycles)
			get_op_code(tmp, arena[tmp->position]);
		tmp->remain_cycles = tmp->remain_cycles > 0 ? tmp->remain_cycles - 1 : tmp->remain_cycles;
		tmp->remain_cycles = 0;
		if (!tmp->remain_cycles)
		{
			if (tmp->op >= 0x01 && tmp->op <= 0x10)
			{
				execute_op(arena, tmp);
			}
			else
				tmp->position = (tmp->position + 1) % MEM_SIZE;
		}
		tmp = tmp->next;
	}
}

int			main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];
	t_carriage		*carriage;
	uint8_t			*arena;

	g_last_alive = parse_players(champs, ac, av);
	arena = init_battlefield(champs);
	carriage = init_carriages();

	print_players(champs); //
	ft_printf("\nCNT: %d\n", g_last_alive); //
	putfile_hex(MEM_SIZE, arena, 1, 32); //
	print_carriages(carriage); //

	battle(arena, carriage);
	return (0);
}
