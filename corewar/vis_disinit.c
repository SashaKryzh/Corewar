/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_disinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:29:54 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/21 20:32:02 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include "corewar.h"

WINDOW *g_arena;
WINDOW *g_statusbar;

static void	print_winner(void)
{
	wattron(g_statusbar, COLOR_PAIR(g_last_alive));
	mvwprintw(g_statusbar, 50, 4, " _       ___                      ");
	mvwprintw(g_statusbar, 51, 4, "| |     / (_)___  ____  ___  _____");
	mvwprintw(g_statusbar, 52, 4, "| | /| / / / __ \\/ __ \\/ _ \\/ ___/");
	mvwprintw(g_statusbar, 53, 4, "| |/ |/ / / / / / / / /  __/ /    ");
	mvwprintw(g_statusbar, 54, 4, "|__/|__/_/_/ /_/_/ /_/\\___/_/     ");
	mvwprintw(g_statusbar, 56, 4, "%30.25s", g_players[g_last_alive - 1].name);
	wattroff(g_statusbar, COLOR_PAIR(g_last_alive));
	refresh();
	wrefresh(g_statusbar);
}

void		disinit(int end)
{
	if (end)
	{
		print_winner();
		while (getch() != 27)
			;
	}
	wattroff(g_arena, A_BOLD);
	wattroff(g_statusbar, A_BOLD);
	endwin();
	exit(0);
}
