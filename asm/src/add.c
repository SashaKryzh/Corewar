/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:07:10 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:06:22 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	valid(t_token **cur)
{
	if (!(*cur)->next || (*cur)->next->type != REGISTER)
		return (err_mesg(NEXT_TOKEN_MUST_BE_REGISTER, (*cur)->line));
	if (!(*cur)->next->next || (*cur)->next->next->type != SEPARATOR)
		return (err_mesg(SEPARATOR_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next ||
		(*cur)->next->next->next->type != REGISTER)
		return (err_mesg(NEXT_TOKEN_MUST_BE_REGISTER, (*cur)->line));
	if (!(*cur)->next->next->next->next
		|| (*cur)->next->next->next->next->type != SEPARATOR)
		return (err_mesg(SEPARATOR_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next->next->next
		|| (*cur)->next->next->next->next->next->type != REGISTER)
		return (err_mesg(NEXT_TOKEN_MUST_BE_REGISTER, (*cur)->line));
	if ((*cur)->next->next->next->next->next->next &&
		(*cur)->next->next->next->next->next->next->line == (*cur)->line)
		return (err_mesg(ONLY_ONE_INSTRUCTION, (*cur)->line));
	return (1);
}

int			add(t_asm *champ, t_token **cur)
{
	char	*temp;

	if (!valid(cur))
		return (0);
	temp = ft_strnew(2);
	temp[0] = 4;
	temp[1] = 84;
	add_to_code(champ, temp, 2);
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1), 1);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1), 1);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1), 1);
	*cur = (*cur)->next;
	return (1);
}
