/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 12:05:25 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:24:47 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	clasify_token(t_asm *champ, t_token *new, char *line, int *j)
{
	int		i;
	char	*token_value;

	if (line[*j] == SEPARATOR_CHAR)
	{
		new->type = SEPARATOR;
		new->value = ft_strdup(",");
		return (1);
	}
	i = *j;
	while (line[*j] && !ft_isspace(line[*j]) && line[*j] != COMMENT_CHAR
			&& line[*j] != SEPARATOR_CHAR)
	{
		if (unknown_character(line[*j]))
			return (err_mesg(UNKNOWN_CHARACTER, new->line));
		(*j)++;
	}
	token_value = ft_strsub(line, i, (*j)-- - i);
	return (token_with_value(champ, new, token_value, new->line));
}

int			add_token(char *line, int i, int *j, t_asm *champ)
{
	t_token	*new;
	t_token	*cur;

	new = (t_token*)malloc(sizeof(t_token));
	new->next = NULL;
	new->line = i;
	new->value = NULL;
	if (!clasify_token(champ, new, line, j))
	{
		ft_strdel(&new->value);
		free(new);
		return (0);
	}
	if (!champ->tokens)
		champ->tokens = new;
	else
	{
		cur = champ->tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (1);
}
