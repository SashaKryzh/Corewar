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

t_cell		*init_battlefield(t_player *champs)
{
	t_cell		*arena;
	int			i;
	int			j;
	int			block;

	arena = (t_cell *)ft_memalloc(sizeof(t_cell) * MEM_SIZE);
	i = 0;
	block = MEM_SIZE / g_last_alive;
	while (i < g_last_alive)
	{
		j = 0;
		while (j < champs[i].code_size)
		{
			arena[i * block + j].id = champs[i].id;
			arena[i * block + j].v = champs[i].code[j];
			j++;
		}
		i++;
	}
	return (arena);
}

t_car		*new_carriage(int id, int position)
{
	t_car	*new;

	new = (t_car *)ft_memalloc(sizeof(t_car));
	new->id = id;
	new->color = id;
	new->position = position;
	new->regs[0] = id * -1;
	return (new);
}

t_car		*init_cars(void)
{
	t_car		*carriage;
	t_car		*tmp;
	int			i;

	i = 1;
	carriage = new_carriage(1, 0);
	while (i < g_last_alive)
	{
		tmp = new_carriage(i + 1, i * (MEM_SIZE / g_last_alive));
		tmp->next = carriage;
		carriage = tmp;
		i++;
	}
	return (carriage);
}
