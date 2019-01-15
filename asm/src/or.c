/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:07:31 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:06:00 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	valid(t_token **cur)
{
	if (!(*cur)->next || (*cur)->next->type == LABEL || (*cur)->next->type
		== INSTRUCTION || (*cur)->next->type == SEPARATOR)
		return (err_mesg(ARGUMENT_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next || (*cur)->next->next->type != SEPARATOR)
		return (err_mesg(SEPARATOR_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next || (*cur)->next->next->next->type == LABEL
		|| (*cur)->next->next->next->type == INSTRUCTION ||
		(*cur)->next->next->next->type == SEPARATOR)
		return (err_mesg(ARGUMENT_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next->next
		|| (*cur)->next->next->next->next->type != SEPARATOR)
		return (err_mesg(SEPARATOR_IS_MISSING, (*cur)->line));
	if (!(*cur)->next->next->next->next->next
		|| (*cur)->next->next->next->next->next->type == REGISTER)
		return (err_mesg(NEXT_TOKEN_MUST_BE_REGISTER, (*cur)->line));
	if ((*cur)->next->next->next->next->next->next &&
		(*cur)->next->next->next->next->next->next->line == (*cur)->line)
		return (err_mesg(ONLY_ONE_INSTRUCTION, (*cur)->line));
	return (1);
}

static void	add_codes(t_asm *champ, t_token **cur)
{
	int32_t	arg_code;

	arg_code = 4;
	if ((*cur)->next->type == DIRECT_LABEL ||
		(*cur)->next->type == DIRECT_VALUE)
		arg_code += 32;
	else if ((*cur)->next->type == INDIRECT_LABEL ||
		(*cur)->next->type == INDIRECT_VALUE)
		arg_code += 48;
	else
		arg_code += 16;
	if ((*cur)->next->next->next->type == DIRECT_LABEL ||
		(*cur)->next->next->next->type == DIRECT_VALUE)
		arg_code += 128;
	else if ((*cur)->next->next->next->type == INDIRECT_LABEL ||
		(*cur)->next->next->next->type == INDIRECT_VALUE)
		arg_code += 192;
	else
		arg_code += 64;
	add_to_code(champ, int_to_hex(arg_code, 1));
}

static void	add_arg(t_asm *champ, t_token **cur)
{
	if ((*cur)->type == INDIRECT_VALUE || (*cur)->type == DIRECT_VALUE)
	{
		if ((*cur)->type == INDIRECT_VALUE)
			add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 2));
		else
			add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 4));
		return ;
	}
	if ((*cur)->type == REGISTER)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1));
		return ;
	}
	if (!get_label_value((*cur)->value, champ, 2 + ((*cur)->type == INDIRECT_LABEL) * 2))
	{
		if ((*cur)->type == DIRECT_LABEL)
		{
			add_new_missed(champ, 2, (*cur)->value);
			add_to_code(champ, ft_strdup("0000"));
			return ;
		}
		add_new_missed(champ, 4, (*cur)->value);
		add_to_code(champ, ft_strdup("00000000"));
	}
}

int			or(t_asm *champ, t_token **cur)
{
	if (!valid(cur))
		return (0);
	add_to_code(champ, ft_strdup("07"));
	add_codes(champ, cur);
	*cur = (*cur)->next;
	add_arg(champ, cur);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_arg(champ, cur);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1));
	*cur = (*cur)->next;
	return (1);
}
