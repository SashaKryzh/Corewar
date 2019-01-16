/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:49:57 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/14 16:42:20 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ncurses.h>
#include <stdlib.h>
#include "op.h"
#include "corewar.h"

#define CARRIGE_ON_GREEN 11
#define CARRIGE_ON_BLUE 12
#define CARRIGE_ON_YELLOW 13
#define CARRIGE_ON_RED 14
#define MOVE_SHIFT(x) wmove(g_statusbar, y, 4); x; y += 2;

WINDOW *g_arena;
WINDOW *g_statusbar;

void	init(void)
{
	initscr();
	g_arena = newwin(66, 194, 0, 0);
	g_statusbar = newwin(66, 50, 0, 195);

	start_color();
	noecho();
	curs_set(0);
	assume_default_colors(182, 0);
	init_pair(0, COLOR_WHITE, COLOR_BLUE);
	init_pair(1, COLOR_GREEN , 0);
	init_pair(2, COLOR_BLUE, 0);
	init_pair(3, COLOR_YELLOW, 0);
	init_pair(4, COLOR_RED, 0);
	init_pair(11, COLOR_WHITE, 49);
	init_pair(12, COLOR_WHITE, 111);
	init_pair(13, COLOR_WHITE, 223);
	init_pair(14, COLOR_WHITE, 205);

	box(g_arena, 0, 0);
	box(g_statusbar, 0, 0);
	wattron(g_arena, A_BOLD);
	wattron(g_statusbar, A_BOLD);

	int y;
	y = 10;
	wmove(g_statusbar, 2, 4);
	wprintw(g_statusbar, "   ______                                  ");
	wmove(g_statusbar, 3, 4);
	wprintw(g_statusbar, "  / ____/___  ________ _      ______ ______");
	wmove(g_statusbar, 4, 4);
	wprintw(g_statusbar, " / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	wmove(g_statusbar, 5, 4);
	wprintw(g_statusbar, "/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	wmove(g_statusbar, 6, 4);
	wprintw(g_statusbar, "\\____/\\____/_/   \\___/|__/|__/\\__,_/_/     ");
	//вывести всех игроков
	MOVE_SHIFT(wprintw(g_statusbar, "Player1: ", "Pasha"))
	MOVE_SHIFT(wprintw(g_statusbar, "Player2: ", "Sasha"))
	MOVE_SHIFT(wprintw(g_statusbar, "Player3: ", "Anton"))
	MOVE_SHIFT(wprintw(g_statusbar, "Player4: ", "Vadym"))
	MOVE_SHIFT(wprintw(g_statusbar, "Cycle: %i", g_cnt_cycles))
	MOVE_SHIFT(wprintw(g_statusbar, "Procceses alive: %i", 4))
	MOVE_SHIFT(wprintw(g_statusbar, "_________________________________________"))
	MOVE_SHIFT(wprintw(g_statusbar, "                CONSTANTS                "))
	MOVE_SHIFT(wprintw(g_statusbar, "CYCLE_TO_DIE: %i", CYCLE_TO_DIE))
	MOVE_SHIFT(wprintw(g_statusbar, "CYCLE_DELTA: %i", CYCLE_DELTA))
	MOVE_SHIFT(wprintw(g_statusbar, "NBR_LIVE: %i", NBR_LIVE))
	MOVE_SHIFT(wprintw(g_statusbar, "MAX_CHECKS: %i", MAX_CHECKS))

	refresh();
	wrefresh(g_arena);
	wrefresh(g_statusbar);
}

void	print_into_arena(t_cell *cells, t_car *carrs)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 1;
	y = 0;
	while (i < 4096)
	{
		if (i % 64 == 0)
		{
			y++;
			x = 1;
		}
		wattron(g_arena, COLOR_PAIR(ft_abs(cells[i].id)));
		mvwprintw(g_arena, y, x, "%02x", cells[i].v);
		wattroff(g_arena, COLOR_PAIR(ft_abs(cells[i].id)));
		x += 3;
		i++;
	}
	while (carrs)
	{
		int x_car;
		int y_car;
		
		wattron(g_arena, COLOR_PAIR(11));
		x_car = (carrs->position * 3) % 64 + 1;
		y_car = (carrs->position) / 64 + 1;
		mvwprintw(g_arena, y_car, x_car, "%02x", cells[carrs->position].v);
		wattroff(g_arena, COLOR_PAIR(11));
		carrs = carrs->next;
	}
	refresh();
	wrefresh(g_arena);
	wrefresh(g_statusbar);
	usleep(10000);
}

// t_cell	*create_cells()
// {
// 	t_cell	*cells;
// 	int 	i;

// 	i = 0;
// 	cells = (t_cell*)malloc(sizeof(t_cell) * 4096);
// 	while (i < 4096)
// 	{
// 		cells[i].v = rand() % 255;
// 		cells[i].id = rand() % 5;
// 		i++;
// 	}
// 	cells[1].id = 11;
// 	cells[2].id = 12;
// 	cells[3].id = 13;
// 	cells[4].id = 14;
// 	return (cells);
// }

void	disinit(void)
{
	getch();
	wattroff(g_arena, A_BOLD);
	wattroff(g_statusbar, A_BOLD);
	endwin();
}

