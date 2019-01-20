/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:49:57 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/18 17:36:44 by vlytvyne         ###   ########.fr       */
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

void	refr(void)
{
	mvwprintw(g_statusbar, 10, 4, "Cycle: %i", g_cnt_cycles);
	refresh();
	wrefresh(g_arena);
	wrefresh(g_statusbar);
	usleep(10000);
}

void	init(void)
{
	initscr();
	g_arena = newwin(66, 195, 0, 0);
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

	MOVE_SHIFT(wprintw(g_statusbar, "Cycle: %i", g_cnt_cycles))
	int i = 0;
	while (g_players[i].id != -1)
	{
		MOVE_SHIFT(wprintw(g_statusbar, "Player %d: %s", i + 1, g_players[i].name))
		i++;
	}
	MOVE_SHIFT(wprintw(g_statusbar, "_________________________________________"))
	MOVE_SHIFT(wprintw(g_statusbar, "                CONSTANTS                "))
	MOVE_SHIFT(wprintw(g_statusbar, "CYCLE_TO_DIE: %i", CYCLE_TO_DIE))
	MOVE_SHIFT(wprintw(g_statusbar, "CYCLE_DELTA: %i", CYCLE_DELTA))
	MOVE_SHIFT(wprintw(g_statusbar, "NBR_LIVE: %i", NBR_LIVE))
	MOVE_SHIFT(wprintw(g_statusbar, "MAX_CHECKS: %i", MAX_CHECKS))

	refr();
}

void	print_carrs(t_cell *cells, t_car *carrs)
{
	int x;
	int y;

	while (carrs)
	{
		wattron(g_arena, COLOR_PAIR(11));
		x = carrs->position % 64 * 3 + 2;
		y = (carrs->position) / 64 + 1;
		mvwprintw(g_arena, y, x, "%02x", cells[carrs->position].v);
		wattroff(g_arena, COLOR_PAIR(11));
		carrs = carrs->next;
	}
}

void	print_bold(t_cell *cells, int position, int size)
{
	int x;
	int y;
	int end;

	end = position + size;
	wattron(g_arena, A_BOLD);
	wattron(g_arena, COLOR_PAIR(ft_abs(cells[position].id)));
	while (position < end)
	{
		x = position % 64 * 3 + 2;
		y = position / 64 + 1;
		mvwprintw(g_arena, y, x, "%02x", cells[position].v);
		position++;
	}
	wattroff(g_arena, COLOR_PAIR(ft_abs(cells[position].id)));
}

void	print_into_arena(t_cell *cells, t_car *carrs)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 2;
	y = 0;
	while (i < 4096)
	{
		if (i % 64 == 0)
		{
			y++;
			x = 2;
		}
		if (cells[i].id != 0)
		{
			wattroff(g_arena, A_BOLD);
			wattron(g_arena, COLOR_PAIR(ft_abs(cells[i].id)));
		}
		mvwprintw(g_arena, y, x, "%02x", cells[i].v);
		wattroff(g_arena, COLOR_PAIR(ft_abs(cells[i].id)));
		wattron(g_arena, A_BOLD);
		x += 3;
		i++;
	}
}

void 		update_view(t_cell *arena)
{
	print_into_arena(arena, g_carriage);
	print_carrs(arena, g_carriage);
	refr();
}

void		show_on_arena(t_cell *arena, int where, int size)
{
	// print_bold(arena, where, size);
	refr();
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

