/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:07:57 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/21 20:29:31 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "op.h"
#include "corewar.h"

WINDOW *g_arena;
WINDOW *g_statusbar;
int		g_delay;

static void	set_colors(void)
{
	start_color();
	assume_default_colors(182, 0);
	init_pair(0, COLOR_WHITE, COLOR_BLUE);
	init_pair(1, COLOR_GREEN, 0);
	init_pair(2, 21, 0);
	init_pair(3, COLOR_YELLOW, 0);
	init_pair(4, COLOR_RED, 0);
	init_pair(11, COLOR_WHITE, 49);
	init_pair(12, COLOR_WHITE, 111);
	init_pair(13, COLOR_WHITE, 223);
	init_pair(14, COLOR_WHITE, 205);
}

static void	print_header(void)
{
	mvwprintw(g_statusbar, 2, 4, "   ______                                  ");
	mvwprintw(g_statusbar, 3, 4, "  / ____/___  ________ _      ______ ______");
	mvwprintw(g_statusbar, 4, 4,
	" / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	mvwprintw(g_statusbar, 5, 4,
	"/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	mvwprintw(g_statusbar, 6, 4,
	"\\____/\\____/_/   \\___/|__/|__/\\__,_/_/     ");
}

static void	print_inf(void)
{
	int i;

	mvwprintw(g_statusbar, 10, 4, "_________________________________________");
	mvwprintw(g_statusbar, 11, 4, "                               BATTLEFLOW");
	mvwprintw(g_statusbar, 13, 4, "Cycle: %i", g_cnt_cycles);
	mvwprintw(g_statusbar, 15, 4, "Cycle to die: %i", g_cycles_to_die);
	mvwprintw(g_statusbar, 17, 4, "_________________________________________");
	mvwprintw(g_statusbar, 18, 4, "                                  PLAYERS");
	i = 0;
	while (g_players[i].id != -1)
	{
		wattron(g_statusbar, COLOR_PAIR(i + 1));
		mvwprintw(g_statusbar, 20 + (i * 2), 4,
		"Player %d: %.25s", i + 1, g_players[i].name);
		wattroff(g_statusbar, COLOR_PAIR(i + 1));
		i++;
	}
	mvwprintw(g_statusbar, 28, 4, "_________________________________________");
	mvwprintw(g_statusbar, 29, 4, "                                CONSTANTS");
	mvwprintw(g_statusbar, 31, 4, "CYCLE_DELTA: %i", CYCLE_DELTA);
	mvwprintw(g_statusbar, 33, 4, "NBR_LIVE: %i", NBR_LIVE);
	mvwprintw(g_statusbar, 35, 4, "MAX_CHECKS: %i", MAX_CHECKS);
}

void		print_options(void)
{
	mvwprintw(g_statusbar, 37, 4, "_________________________________________");
	mvwprintw(g_statusbar, 38, 4, "                                  OPTIONS");
	mvwprintw(g_statusbar, 40, 4, "[SPACE] - pause/resume");
	mvwprintw(g_statusbar, 42, 4, "[F] - speed up");
	mvwprintw(g_statusbar, 44, 4, "[S] - slow down");
	mvwprintw(g_statusbar, 46, 4, "[ESC] - exit");
}

void		init(void)
{
	initscr();
	g_arena = newwin(66, 195, 0, 0);
	g_statusbar = newwin(66, 50, 0, 195);
	g_delay = 10000;
	timeout(0);
	noecho();
	curs_set(0);
	set_colors();
	box(g_arena, 0, 0);
	box(g_statusbar, 0, 0);
	wattron(g_arena, A_BOLD);
	wattron(g_statusbar, A_BOLD);
	print_header();
	print_inf();
	print_options();
	refr();
}
