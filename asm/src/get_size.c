/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:44:15 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 12:34:41 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	instruction_size(t_token *cur, int *dir_size)
{
	if (ft_strequ(cur->value, "zjmp") || ft_strequ(cur->value, "ldi") ||
		ft_strequ(cur->value, "sti") || ft_strequ(cur->value, "fork") ||
		ft_strequ(cur->value, "lldi") || ft_strequ(cur->value, "lfork"))
		*dir_size = 2;
	else
		*dir_size = 4;
	if (ft_strequ(cur->value, "live") || ft_strequ(cur->value, "zjmp") ||
		ft_strequ(cur->value, "lfork") || ft_strequ(cur->value, "fork"))
		return (1);
	else
		return (2);
}

void		get_size(t_asm *champ)
{
	int		dir_size;
	t_token	*cur;

	champ->size = 0;
	cur = champ->tokens;
	while (cur)
	{
		if (cur->type == LABEL)
			add_label(champ, cur);
		else if (cur->type == INSTRUCTION)
			champ->size += instruction_size(cur, &dir_size);
		else if (cur->type == REGISTER)
			champ->size += 1;
		else if (cur->type == DIRECT_VALUE || cur->type == DIRECT_LABEL)
			champ->size += dir_size;
		else if (cur->type == INDIRECT_VALUE || cur->type == INDIRECT_LABEL)
			champ->size += 2;
		cur = cur->next;
	}
}
