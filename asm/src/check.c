/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 11:25:31 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/13 11:46:03 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			label_exists(char *label, t_asm *champ)
{
	t_token		*cur;

	cur = champ->tokens;
	while (cur)
	{
		if (cur->type == LABEL && ft_strequ(cur->value, label))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int			check_rest(char *str, int start)
{
	while (str[++start])
		if (str[start] == COMMENT_CHAR)
			return (1);
		else if (!ft_isspace(str[start]))
			return (0);
	return (1);
}
