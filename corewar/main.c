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

int			get_dir(uint8_t *arena, t_carriage *car, uint8_t size)
{
	char	n[4];
	int		res;

	ft_bzero(n, 4);
	if (size == 2)
		ft_memcpy(&n[2], arena, size);
	else
		ft_memcpy(n, arena, size);
	ft_memcpy(&res, n, 4);
	ft_memrev(&res, 4); // BIG ENDIAN
	return (res);
}

void		live_op(uint8_t *arena, t_carriage *car)
{
	return ;
}

void		sti_op(uint8_t *arena, t_carriage *car)
{
	int res;
	int	reg;
	int	arg2;
	int	arg3;

	reg = car->regs[get_reg_num(arena, car, 1) - 1];
	arg2 = get_dir(to_arg(arena, car, 2), car, OP.t_dir_size);
	arg3 = get_dir(to_arg(arena, car, 3), car, OP.t_dir_size);
	ft_printf("reg: %d, arg2: %d, arg3: %d\n", reg, arg2, arg3); //
	res = (arg2 + arg3) % IDX_MOD;
	arena[(car->position + res) % MEM_SIZE] = reg;
}

void		execute_op(uint8_t *arena, t_carriage *car)
{
	if (arena[car->position] == 0x0b)
		sti_op(arena, car);
	else
		ft_printf("Nea...\n");
}

void		get_op_code(t_carriage *car, uint8_t op)
{
	car->op = op;
	if (op >= 0x01 && op <= 0x10)
		car->remain_cycles = g_op[op - 1].to_wait;
}

void		manage_op(uint8_t *arena, t_carriage *car)
{
	if (g_op[car->op - 1].is_args_types)
	{
		if (!get_op_data(arena, car))
		{
			skip_op(arena, car);
			exit_func("Invalid data, skip command");
		}
	}
	execute_op(arena, car);
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
				manage_op(arena, tmp);
			}
			else
				tmp->position = (tmp->position + 1) % MEM_SIZE;
		}
		exit(0); // for tests
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
