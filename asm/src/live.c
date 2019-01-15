/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:06:53 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:06:00 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	valid(t_token **cur)
{
	if (!(*cur)->next || !((*cur)->next->type == DIRECT_VALUE ||
		(*cur)->next->type == DIRECT_LABEL))
		return (err_mesg(NEXT_TOKEN_MUST_BE_DIRECT, (*cur)->line));
	if ((*cur)->next->next && (*cur)->next->next->line == (*cur)->line)
		return (err_mesg(ONLY_ONE_INSTRUCTION, (*cur)->line));
	return (1);
}

static void	add_first(t_asm *champ, t_token **cur)
{
	if ((*cur)->type == DIRECT_VALUE)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 4));
		return ;
	}
	if (!get_label_value((*cur)->value, champ, 4))
	{
		add_new_missed(champ, 4, (*cur)->value);
		add_to_code(champ, ft_strdup("00000000"));
	}
}

int			live(t_asm *champ, t_token **cur)
{
	if (!valid(cur))
		return (0);
	add_to_code(champ, ft_strdup("01"));
	*cur = (*cur)->next;
	add_first(champ, cur);
	*cur = (*cur)->next;
	return (1);
}
