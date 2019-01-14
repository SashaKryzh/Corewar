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

#include <ncurses.h>
#include <stdlib.h>
#include "op_42.h"

#define CARRIGE_ON_GREEN 11
#define CARRIGE_ON_BLUE 12
#define CARRIGE_ON_YELLOW 13
#define CARRIGE_ON_RED 14
#define MOVE_SHIFT(x) wmove(statusbar, y, 4); x; y += 2;

typedef struct	s_cell
{
	int			val;
	int			player_id;
}				t_cell;


void	init(WINDOW *arena, WINDOW *statusbar)
{
	start_color();
	noecho();
	curs_set(0);
	assume_default_colors(182, 0);
	init_pair(1, COLOR_GREEN , 0);
	init_pair(2, COLOR_BLUE, 0);
	init_pair(3, COLOR_YELLOW, 0);
	init_pair(4, COLOR_RED, 0);
	init_pair(11, COLOR_WHITE, 49);
	init_pair(12, COLOR_WHITE, 111);
	init_pair(13, COLOR_WHITE, 223);
	init_pair(14, COLOR_WHITE, 205);

	box(arena, 0, 0);
	box(statusbar, 0, 0);
	wattron(arena, A_BOLD);
	wattron(statusbar, A_BOLD);

	int y;
	y = 10;
	wmove(statusbar, 2, 4);
	wprintw(statusbar, "   ______                                  ");
	wmove(statusbar, 3, 4);
	wprintw(statusbar, "  / ____/___  ________ _      ______ ______");
	wmove(statusbar, 4, 4);
	wprintw(statusbar, " / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	wmove(statusbar, 5, 4);
	wprintw(statusbar, "/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	wmove(statusbar, 6, 4);
	wprintw(statusbar, "\\____/\\____/_/   \\___/|__/|__/\\__,_/_/     ");
	//вывести всех игроков
	MOVE_SHIFT(wprintw(statusbar, "Player1: ", "Pasha"))
	MOVE_SHIFT(wprintw(statusbar, "Player2: ", "Sasha"))
	MOVE_SHIFT(wprintw(statusbar, "Player3: ", "Anton"))
	MOVE_SHIFT(wprintw(statusbar, "Player4: ", "Vadym"))
	MOVE_SHIFT(wprintw(statusbar, "Cycle: %i", 123))
	MOVE_SHIFT(wprintw(statusbar, "Procceses alive: %i", 4))
	MOVE_SHIFT(wprintw(statusbar, "_________________________________________"))
	MOVE_SHIFT(wprintw(statusbar, "                CONSTANTS                "))
	MOVE_SHIFT(wprintw(statusbar, "CYCLE_TO_DIE: %i", CYCLE_TO_DIE))
	MOVE_SHIFT(wprintw(statusbar, "CYCLE_DELTA: %i", CYCLE_DELTA))
	MOVE_SHIFT(wprintw(statusbar, "NBR_LIVE: %i", NBR_LIVE))
	MOVE_SHIFT(wprintw(statusbar, "MAX_CHECKS: %i", MAX_CHECKS))

}

void	print_into_arena(WINDOW *arena, t_cell *cells)
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
		wattron(arena, COLOR_PAIR(cells[i].player_id));
		mvwprintw(arena, y, x, "%02x", cells[i].val);
		wattroff(arena, COLOR_PAIR(cells[i].player_id));
		x += 3;
		i++;
	}
}

t_cell	*create_cells()
{
	t_cell	*cells;
	int 	i;

	i = 0;
	cells = (t_cell*)malloc(sizeof(t_cell) * 4096);
	while (i < 4096)
	{
		cells[i].val = rand() % 255;
		cells[i].player_id = rand() % 5;
		i++;
	}
	cells[1].player_id = 11;
	cells[2].player_id = 12;
	cells[3].player_id = 13;
	cells[4].player_id = 14;
	return (cells);
}

int		main()
{
	initscr();
	WINDOW *arena;
	WINDOW *statusbar;
	arena = newwin(66, 194, 0, 0);
	statusbar = newwin(66, 50, 0, 195);
	init(arena, statusbar);

	t_cell *cells;
	cells = create_cells();
	print_into_arena(arena, cells);

	refresh();
	wrefresh(arena);
	wrefresh(statusbar);
	wattroff(arena, A_BOLD);
	wattroff(statusbar, A_BOLD);

	getch();
	endwin();
}

