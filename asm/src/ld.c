/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:06:59 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 16:18:23 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	valid(t_token **cur)
{
	if (!(*cur)->next || !((*cur)->next->type == DIRECT_VALUE ||
		(*cur)->next->type == DIRECT_LABEL ||
		(*cur)->next->type == INDIRECT_VALUE ||
		(*cur)->next->type == INDIRECT_LABEL))
		return (err_mesg(NEXT_TOKEN_MUST_BE_DIR_OR_IN, (*cur)->line));
	if (!(*cur)->next->next || (*cur)->next->next->type != SEPARATOR)
		return (err_mesg(SEPARATOR_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next || (*cur)->next->next->next->type != REGISTER)
		return (err_mesg(NEXT_TOKEN_MUST_BE_REGISTER, (*cur)->line));
	if ((*cur)->next->next->next->next &&
		(*cur)->next->next->next->next->line == (*cur)->line)
		return (err_mesg(ONLY_ONE_INSTRUCTION, (*cur)->line));
	return (1);
}

static void	add_codes(t_asm *champ, t_token **cur)
{
	int32_t	arg_code;

	arg_code = 16;
	if ((*cur)->next->type == DIRECT_LABEL ||
			(*cur)->next->type == DIRECT_VALUE)
		arg_code += 128;
	else
		arg_code += 192;
	add_to_code(champ, int_to_hex(arg_code, 1), 1);
}

static int	add_first(t_asm *champ, t_token **cur, int start)
{
	if ((*cur)->type == INDIRECT_VALUE)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 2), 2);
		return (1);
	}
	if ((*cur)->type == DIRECT_VALUE)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 4), 4);
		return (1);
	}
	if ((*cur)->type == INDIRECT_LABEL)
		return (get_label_value(cur, champ, 2, start));
	return (get_label_value(cur, champ, 4, start));
}

int			ld(t_asm *champ, t_token **cur)
{
	char	*temp;
	int		start;

	if (!valid(cur))
		return (0);
	start = champ->cur_pos;
	temp = ft_strnew(1);
	temp[0] = 2;
	add_to_code(champ, temp, 1);
	add_codes(champ, cur);
	*cur = (*cur)->next;
	if (!add_first(champ, cur, start))
		return (0);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1), 1);
	*cur = (*cur)->next;
	return (1);
}
