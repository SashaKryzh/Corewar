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

int			g_visual;
int			g_dump;

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
	perror(msg);
	exit(0);
}

int			main(int ac, char *av[])
{
	t_cell			*arena;

	g_last_alive = parse_players(g_players, ac, av);
	g_cnt_cars = g_last_alive;
	// ft_printf("last alive: %d, visu: %d, dump: %d\n", g_last_alive, g_visual, g_dump); //
	arena = init_battlefield(g_players);
	g_carriage = init_cars();

	// print_players(g_players); //
	// ft_printf("\nCNT: %d\n", g_last_alive); //
	// putfile_hex(MEM_SIZE, arena, 1, 32); //
	// print_cars(g_carriage); //
	// ft_printf("cnt cars: %d\n", g_cnt_cars);
	// ft_printf("\n");

	if (g_visual)
		init();
	battle(arena, g_carriage);
	if (g_visual)
		disinit();
	return (0);
}
