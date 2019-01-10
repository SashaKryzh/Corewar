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

int		check_reg_num(uint8_t *arena, t_carriage *car, int reg_pos)
{
	int			reg_num;
	uint8_t		to_jump;
	uint8_t		i;

	i = 0;
	to_jump = 1;
	while (i < reg_pos)
	{
		to_jump += car->args_sizes[i];
		i++;
	}
	reg_num = arena[(car->position + 1 + to_jump) % MEM_SIZE];
	if (reg_num <= 0 || reg_num > REG_NUMBER)
	{
		ft_printf("Invalid REG NUMBER\n");
		return (0);
	}
	ft_printf("num: %d\n", reg_num);
	return (1);
}

int		get_op_data(uint8_t *arena, t_carriage *car)
{
	uint8_t		byte;
	uint8_t		i;
	uint8_t		j;
	uint8_t		ret;

	i = 6;
	j = 0;
	ret = 1;
	byte = arena[(car->position + 1) % MEM_SIZE];
	while (j < g_op[car->op - 1].args_num)
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
		else if (((byte >> i) % 4) == REG_CODE)
		{
			ft_printf("T_REG ");
			car->args_sizes[j] = 1;
			if (!check_reg_num(arena, car, j))
				ret = 0;
		}
		else
			car->args_sizes[j] = 0;
		if (!(g_op[car->op - 1].args_types[j] >> ((byte >> i) % 4 - 1)))
		{
			ft_printf("Error in ARGS TYPES\n");
			ret = 0;
		}
		i -= 2;
		j++;
	}
	return (ret);
}

void		skip_invalid_op(uint8_t *arena, t_carriage *car)
{
	int i;

	i = 0;
	ft_printf("from: %d ", car->position);
	car->position += 2;
	while (i < g_op[car->op - 1].args_num)
	{
		car->position += car->args_sizes[i];
		ft_printf("%d ", car->args_sizes[i]);
		i++;
	}
	car->position %= MEM_SIZE;
	ft_printf("to: %d\n", car->position);
}

void		execute_op(uint8_t *arena, t_carriage *car)
{
	if (g_op[car->op - 1].is_args_types)
	{
		if (!get_op_data(arena, car))
		{
			skip_invalid_op(arena, car);
			exit_func("Invalid data, skip command");
		}
	}
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
				ft_printf("%s:\n", g_op[tmp->op - 1].name);
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

	ft_printf("\n");
	battle(arena, carriage);
	return (0);
}
