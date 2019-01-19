/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 12:47:31 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:46:48 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	delete_labels(t_asm *champ)
{
	t_label	*cur;
	t_label	*temp;

	cur = champ->labels;
	while (cur)
	{
		temp = cur->next;
		if (cur->label_name)
			ft_strdel(&cur->label_name);
		free(cur);
		cur = temp;
	}
}

static void	delete_tokens(t_asm *champ)
{
	t_token	*cur;
	t_token	*temp;

	cur = champ->tokens;
	while (cur)
	{
		temp = cur->next;
		ft_strdel(&cur->value);
		free(cur);
		cur = temp;
	}
}

void		delete_champ(t_asm *champ)
{
	if (champ->name)
		ft_strdel(&champ->name);
	if (champ->comment)
		ft_strdel(&champ->comment);
	if (champ->code)
		ft_strdel(&champ->code);
	if (champ->tokens)
		delete_tokens(champ);
	if (champ->labels)
		delete_labels(champ);
}
