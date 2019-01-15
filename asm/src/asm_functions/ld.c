/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:06:59 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/13 15:26:54 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int	valid(t_asm *champ, t_token **cur)
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
	if ((*cur)->next->type == DIRECT_LABEL || (*cur)->next->type == DIRECT_VALUE)
		arg_code += 128;
	else
		arg_code += 192;
	add_to_code(champ, int_to_hex(arg_code, 1));
}

static void	add_first(t_asm *champ, t_token **cur)
{
	if ((*cur)->type == DIRECT_VALUE || (*cur)->type == INDIRECT_VALUE)
	{
		add_to_code(champ, int_to_hex(ft_atoi((*cur)->value),
			2 + ((*cur)->type == DIRECT_VALUE) * 2));
		return ;
	}
	if (!get_label_value((*cur)->value, champ, 2 + ((*cur)->type == DIRECT_LABEL) * 2))
	{
		if ((*cur)->type == INDIRECT_LABEL)
		{
			add_new_missed(champ, 2, (*cur)->value);
			add_to_code(champ, ft_strdup("0000"));
		}
		else
		{
			add_new_missed(champ, 4, (*cur)->value);
			add_to_code(champ, ft_strdup("00000000"));
		}
	}
}

int			ld(t_asm *champ, t_token **cur)
{
	char	*temp;

	if (!valid(champ, cur))
		return (0);
	add_to_code(champ, ft_strdup("02"));
	add_codes(champ, cur);
	*cur = (*cur)->next;
	add_first(champ, cur);
	*cur = (*cur)->next;
	*cur = (*cur)->next;
	add_to_code(champ, int_to_hex(ft_atoi((*cur)->value), 1));
	*cur = (*cur)->next;
	return (1);
}