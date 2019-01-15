/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:32:18 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:55:43 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		fill_missed_labels(t_asm *champ)
{
	t_missed_label	*cur;
	t_label			*label;
	char			*temp;
	int32_t			value;
	int				i;

	cur = champ->missed_labels;
	while (cur)
	{
		label = champ->labels;
		while (!ft_strequ(cur->label_name, label->label_name))
			label = label->next;
		value = (int32_t)(cur->code_pos - label->code_pos);
		temp = int_to_hex(value, cur->size);
		i = -1;
		while (temp[++i])
		{
			*(cur->code_pos) = temp[i];
			cur->code_pos++;
		}
		cur = cur->next;
	}
}

void		add_new_missed(t_asm *champ, int size, char *name)
{
	t_missed_label	*new;
	t_label			*cur;
	char			*pos;

	cur = champ->labels;
	new = (t_missed_label*)malloc(sizeof(t_missed_label));
	new->next = champ->missed_labels;
	champ->missed_labels = new;
	new->label_name = name;
	new->size = size;
	pos = champ->code;
	while (*pos)
		pos++;
	new->code_pos = pos;
}

int			get_label_value(char *label_name, t_asm *champ, int size)
{
	t_label		*cur;
	char		*pos;
	int32_t		value;

	cur = champ->labels;
	while (cur)
	{
		if (ft_strequ(cur->label_name, label_name))
			break ;
		cur = cur->next;
	}
	if (!cur)
		return (0);
	pos = champ->code;
	while (*pos)
		pos++;
	value = (int32_t)(pos - cur->code_pos);
	add_to_code(champ, int_to_hex(value, size));
	return (1);
}

void		add_label(t_asm *champ, t_token *label)
{
	t_label	*new;
	char	*pos;

	new = (t_label*)malloc(sizeof(t_label));
	new->label_name = label->value;
	pos = champ->code;
	while (*pos)
		pos++;
	new->code_pos = pos;
	new->next = champ->labels;
	champ->labels = new;
}
