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

t_car	*g_carriage;

int		g_last_alive;
int		g_cnt_cars;

int		g_cnt_cycles;
int		g_cnt_live;
int		g_cnt_checks;

int		g_cycles_to_die = CYCLE_TO_DIE;

void		exit_func(char *msg)
{
	ft_printf("[Error]: %s\n", msg);
	exit(0);
}

void		live_op(uint8_t *arena, t_car *car)
{
	return ;
}

int			get_dir(uint8_t *arena, t_car *car, int start)
{
	char	n[4];
	int		res;
	int		i;

	ft_bzero(n, 4);
	i = 0;
	while (i < OP.t_dir_size)
	{
		n[i + OP.t_dir_size % 4] = arena[(start + i) % MEM_SIZE];
		i++;
	}
	ft_memcpy(&res, n, 4);
	// ft_printf("%d\n", res);
	// putbytes_bit(&res, 4);
	ft_memrev(&res, 4); // BIG ENDIAN
	return (res);
}

int			get_ind(uint8_t *arena, t_car *car, int start)
{
	char	n[4];
	int		res;
	int		i;

	ft_bzero(n, IND_SIZE);
	i = 0;
	while (i < IND_SIZE)
	{
		n[2] = arena[(start + i) % MEM_SIZE];
		i++;
	}
	ft_memcpy(&res, n, sizeof(n));
	ft_memrev(&res, sizeof(res));
	return (res);
}

void		sti_op(uint8_t *arena, t_car *car)
{
	int addr;
	int	i;
	int	reg;
	int	args[2];

	reg = car->regs[get_reg_num(arena, car, 1) - 1];
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i + 1] == DIR_CODE)
			args[i] = get_dir(arena, car, to_arg(arena, car, i + 2));
		else if (car->args_types[i + 1] == IND_CODE)
			args[i] = get_ind(arena, car, to_arg(arena, car, i + 2));
		else
			args[i] = car->regs[get_reg_num(arena, car, i + 2) - 1];
		i++;
	}
	ft_printf("reg: %d, arg2: %d, arg3: %d\n", reg, args[0], args[1]); //
	// putbytes_bit((char *)(&reg), sizeof(reg));
	addr = (args[0] + args[1]) % IDX_MOD;
	ft_memrev(&reg, sizeof(reg));
	put_on_arena(arena, (car->position + addr) % MEM_SIZE, (uint8_t *)(&reg), REG_SIZE);
}

void		fork_op(uint8_t *arena, t_car *car)
{
	t_car	*new;
	int		where;

	where = get_dir(arena, car, 1);
	where %= IDX_MOD;
	new = (t_car *)ft_memalloc(sizeof(t_car));
	new->id = ++g_cnt_cars;
	new->carry = car->carry;
	new->last_live = car->last_live;
	new->position = (car->position + where) % MEM_SIZE;
	ft_memcpy(new->regs, car->regs, sizeof(car->regs));
	new->next = g_carriage;
	g_carriage = new;
	// print_cars(g_carriage);
}

void		execute_op(uint8_t *arena, t_car *car)
{
	if (car->op == 0x0B)
		sti_op(arena, car);
	else if (car->op == 0x01)
		live_op(arena, car);
	else if (car->op == 0x0C)
		fork_op(arena, car);
	else
		ft_printf("Nea...\n");
}

void		get_op_code(t_car *car, uint8_t op)
{
	car->op = op;
	if (op >= 0x01 && op <= 0x10)
		car->remain_cycles = g_op[op - 1].to_wait;
}

void		manage_op(uint8_t *arena, t_car *car)
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
	skip_op(arena, car);
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
				if (tmp->op == 0x0B || tmp->op == 0x0C)
				{
					ft_printf("%s:\n", g_op[tmp->op - 1].name);
					manage_op(arena, tmp);
				}
				else
					tmp->position = (tmp->position + 1) % MEM_SIZE;
			}
			tmp = tmp->next;
		}
		g_cnt_cycles++;
		if (g_cnt_cycles == 800)
		{
			// putfile_hex(MEM_SIZE, arena, 1, 32); //
			exit(1);
		}
	}
}

int			main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];
	t_car		*carriage;
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
	ft_printf("cnt cars: %d\n", g_cnt_cars);
	ft_printf("\n");
	battle(arena, carriage);
	return (0);
}
