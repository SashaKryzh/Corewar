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

int		g_last_alive;
int		g_cnt_cycles;
int		g_cnt_live;
int		g_cycles_to_die = CYCLE_TO_DIE;
int		g_cnt_checks;

void	exit_func(char *msg)
{
	ft_printf("[Error]: %s\n", msg);
	exit(0);
}

uint8_t	*init_battlefield(t_player *champs)
{
	uint8_t		*arena;
	int			i;
	int			j;
	int			block;

	arena = (uint8_t *)ft_memalloc(sizeof(uint8_t) * MEM_SIZE);
	i = 0;
	block = MEM_SIZE / g_last_alive;
	while (i < g_last_alive)
	{
		j = 0;
		while (j < champs[i].code_size)
		{
			arena[i * block + j] = champs[i].code[j];
			j++;
		}
		i++;
	}
	return (arena);
}

int		main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];
	uint8_t			*arena;

	g_last_alive = parse_players(champs, ac, av);
	print_players(champs); //
	ft_printf("\nCNT: %d\n", g_last_alive);
	arena = init_battlefield(champs);
	putfile_hex(MEM_SIZE, arena, 1, 32); // 

	return (0);
}
