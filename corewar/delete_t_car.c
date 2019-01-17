/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_t_car.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:34:02 by pzakala           #+#    #+#             */
/*   Updated: 2019/01/16 15:34:07 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void 	delete_t_car(t_car *tmp)
{
	t_car *s;

	if (g_carriage == tmp)
	{
		g_carriage = NULL;
		free(tmp);
		return ;
	}
	s = g_carriage;
	while (s->next && s->next != tmp)
		s = s->next;
	if (!s->next)
	{
		ft_printf("Shoto ne tak!\n");
		exit(1);
	}
	s->next = s->next->next;
	free(tmp);
}
