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

#include "corewar.h"
#include "stdlib.h"

void 	delete_t_car(t_car **head, t_car *tmp)
{
	t_car *s;

	if (*head == tmp)
	{
		*head = (*head)->next;
		free(tmp);
	}
	s = *head;
	while (s->next && s->next != tmp)
		s = s->next;
	if (!(s->next))
		return ;
	s->next = tmp->next;
	free(tmp);
}