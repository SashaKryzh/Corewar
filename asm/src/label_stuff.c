/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:32:18 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:44:59 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			get_label_value(t_token **label, t_asm *champ, int size, int start)
{
	t_label		*cur;
	int32_t		value;

	cur = champ->labels;
	while (cur)
	{
		if (ft_strequ(cur->label_name, (*label)->value))
			break ;
		cur = cur->next;
	}
	if (!cur)
		return (err_mesg(LABEL_DOES_NOT_EXIST, (*label)->line));
	value = cur->code_pos - start;
	add_to_code(champ, int_to_hex(value, size), size);
	return (1);
}

void		add_label(t_asm *champ, t_token *label)
{
	t_label	*new;

	new = (t_label*)malloc(sizeof(t_label));
	new->label_name = ft_strdup(label->value);
	new->code_pos = champ->size;
	new->next = champ->labels;
	champ->labels = new;
}
