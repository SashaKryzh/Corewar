/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:06:53 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 16:44:33 by amoroziu         ###   ########.fr       */
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

static int	add_first(t_asm *champ, t_token **cur, int start)
{
	if ((*cur)->type == DIRECT_VALUE)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 4), 4);
		return (1);
	}
	return (get_label_value(cur, champ, 4, start));
}

int			live(t_asm *champ, t_token **cur)
{
	char	*temp;
	int		start;

	if (!valid(cur))
		return (0);
	start = champ->cur_pos;
	temp = ft_strnew(1);
	temp[0] = 1;
	add_to_code(champ, temp, 1);
	*cur = (*cur)->next;
	if (!add_first(champ, cur, start))
		return (0);
	*cur = (*cur)->next;
	return (1);
}
