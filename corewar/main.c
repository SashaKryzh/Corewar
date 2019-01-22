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

int			g_start_to_show;

int			g_visual;
int			g_debug;
int			g_format = 32;
int			g_dump = -1;

t_player	g_players[MAX_PLAYERS + 1];
t_car		*g_carriage;

int			g_cnt_players;
int			g_cnt_cars;
int			g_last_alive;

int			g_cycles_to_die = CYCLE_TO_DIE;

int			g_cnt_live;
int			g_cnt_cycles = 1;

void		exit_func(char *msg)
{
	ft_printf("%s\n", msg);
	exit(1);
}

int			main(int ac, char *av[])
{
	t_cell			*arena;

	g_last_alive = parse_players(g_players, ac, av);
	g_cnt_cars = g_last_alive;
	g_cnt_players = g_last_alive;
	arena = init_battlefield(g_players);
	g_carriage = init_cars();
	check_flags_priority();
	introduce_champs(g_players);
	if (!g_dump)
		putarena(arena);
	if (g_visual)
		init();
	battle(arena);
	return (0);
}
