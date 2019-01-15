/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:08:03 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/14 13:08:04 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	change_dir_size(int *dir_size, char *instr)
{
	if (ft_strequ(instr, "zjmp") || ft_strequ(instr, "ldi") ||
		ft_strequ(instr, "sti") || ft_strequ(instr, "fork") ||
		ft_strequ(instr, "lldi") || ft_strequ(instr, "lfork"))
		*dir_size = 2;
	else
		*dir_size = 4;
}

static int	token_size(int dir_size, t_token *cur)
{
	if (cur->type == REGISTER)
		return (1);
	if (cur->type == INDIRECT_VALUE || cur->type == INDIRECT_LABEL)
		return (2);
	if (cur->type == DIRECT_VALUE || cur->type == DIRECT_LABEL)
		return (dir_size);
	if (cur->type == INSTRUCTION)
	{
		if (ft_strequ(cur->value, "live") || ft_strequ(cur->value, "zjmp") ||
			ft_strequ(cur->value, "lfork") || ft_strequ(cur->value, "fork"))
			return (1);
		return (2);
	}
	else
		return (0);
}

void		prepare_labels(t_asm *champ)
{
	t_token	*cur;
	int		dir_size;
	int		size;

	dir_size = 4;
	cur = champ->tokens;
	size = 0;
	while (cur)
	{
		if (cur->type == LABEL)
		{
			ft_strdel(&cur->value);
			cur->value = ft_itoa(size);
		}
		else
			size += token_size(dir_size, cur);
		if (cur->type == INSTRUCTION)
			change_dir_size(&dir_size, cur->value);
		cur = cur->next;
	}
}
