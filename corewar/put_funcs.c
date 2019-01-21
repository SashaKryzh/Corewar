/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 07:59:23 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 07:59:23 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		introduce_champs(t_player *champs)
{
	int i;

	if (g_visual)
		return ;
	printf("Introducing contestants...\n");
	i = 0;
	while (champs[i].id != -1)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" ",
			champs[i].id, champs[i].code_size, champs[i].name);
		printf("(\"%s\") !\n", champs[i].comment);
		i++;
	}
}

void		putarena(t_cell *arena)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (g_debug && i == 0)
			printf("0x0000 : ");
		else if (g_debug && i % g_format == 0)
			printf("%#06x : ", i);
		printf("%02x ", arena[i].v);
		if ((i + 1) % g_format == 0)
			printf("\n");
		i++;
	}
	system("leaks corewar");
	exit(0);
}

void		is_winner(void)
{
	if (!g_carriage)
	{
		if (!g_visual)
		{
			printf("Contestant %d, \"%s\", has won !\n",
				g_last_alive, g_players[g_last_alive - 1].name);
		}
		else
			disinit();
		system("leaks corewar");
		exit(0);
	}
}
