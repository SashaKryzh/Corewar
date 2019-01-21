/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:49:57 by vlytvyne          #+#    #+#             */
/*   Updated: 2019/01/21 20:30:44 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ncurses.h>
#include <stdlib.h>
#include "op.h"
#include "corewar.h"

WINDOW *g_arena;
WINDOW *g_statusbar;
int		g_delay;

void	refr_statusbar(void)
{
	refresh();
	wrefresh(g_statusbar);
}

void	refr(void)
{
	char	ch;

	mvwprintw(g_statusbar, 13, 4, "Cycle: %i", g_cnt_cycles, g_delay);
	mvwprintw(g_statusbar, 15, 4, "Cycle to die: %i", g_cycles_to_die);
	ch = getch();
	if (ch == 32)
	{
		mvwprintw(g_statusbar, 63, 19, "***PAUSE***");
		refr_statusbar();
		while ((ch = getch()) != 32 && ch != 27)
			;
		mvwprintw(g_statusbar, 63, 19, "           ");
		refr_statusbar();
	}
	if (ch == 27)
		disinit(0);
	if (ch == 'f' && g_delay > 10)
		g_delay /= 10;
	if (ch == 's' && g_delay < 100000)
		g_delay *= 10;
	refresh();
	wrefresh(g_arena);
	wrefresh(g_statusbar);
	usleep(g_delay);
}

void	print_carrs(t_cell *cells, t_car *carrs)
{
	int x;
	int y;

	while (carrs)
	{
		wattron(g_arena, COLOR_PAIR(carrs->color + 10));
		x = carrs->position % 64 * 3 + 2;
		y = (carrs->position) / 64 + 1;
		mvwprintw(g_arena, y, x, "%02x", cells[carrs->position].v);
		wattroff(g_arena, COLOR_PAIR(carrs->color + 10));
		carrs = carrs->next;
	}
}

void	print_into_arena(t_cell *cells)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 2;
	y = 0;
	while (i < MEM_SIZE)
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

void	update_view(t_cell *arena)
{
	print_into_arena(arena);
	print_carrs(arena, g_carriage);
	refr();
}
