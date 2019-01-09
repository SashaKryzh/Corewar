/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_battle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:18:09 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/09 15:18:09 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

uint8_t		*init_battlefield(t_player *champs)
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

t_carriage	*new_carriage(int id, int position)
{
	t_carriage	*new;

	new = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	new->id = id;
	new->position = position;
	new->regs[0] = id * -1;
	return (new);
}

t_carriage	*init_carriages(void)
{
	t_carriage	*carriage;
	t_carriage	*tmp;
	int			i;

	i = 1;
	carriage = new_carriage(1, 0);
	carriage->regs[0] = -1;
	while (i < g_last_alive)
	{
		tmp = new_carriage(i + 1, i * MEM_SIZE / g_last_alive);
		tmp->next = carriage;
		carriage = tmp;
		i++;
	}
	return (carriage);
}
