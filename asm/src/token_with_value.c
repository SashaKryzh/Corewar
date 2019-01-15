/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_with_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 12:50:39 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:58:59 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	is_instruction(char *str)
{
	return (ft_strequ(str, "live") || ft_strequ(str, "ld") ||
			ft_strequ(str, "st") || ft_strequ(str, "add") ||
			ft_strequ(str, "sub") || ft_strequ(str, "and") ||
			ft_strequ(str, "or") || ft_strequ(str, "xor") ||
			ft_strequ(str, "zjmp") || ft_strequ(str, "ldi") ||
			ft_strequ(str, "sti") || ft_strequ(str, "fork") ||
			ft_strequ(str, "lldi") || ft_strequ(str, "lld") ||
			ft_strequ(str, "lfork") || ft_strequ(str, "aff"));
}

static int	get_direct_value(t_asm *champ, t_token *token, char *value, int line_idx)
{
	int		i;

	if (value[1] != LABEL_CHAR)
	{
		i = 1 + (value[2] == '-');
		while (ft_isdigit(value[++i]))
			;
		if (value[i])
			return (err_mesg(BAD_CHARACTER_IN_DIRECT_VALUE, line_idx));
		token->value = ft_strsub(value, 1, ft_strlen(value) - 1);
		token->type = DIRECT_VALUE;
		return (1);
	}
	i = 1;
	while (value[++i] && ft_strchr(LABEL_CHARS, value[i]))
		;
	if (value[i])
		return (err_mesg(BAD_CHARACTER_IN_LABEL, line_idx));
	token->value = ft_strsub(value, 2, ft_strlen(value) - 2);
	token->type = DIRECT_LABEL;
	if (!label_exists(value, champ))
		return (err_mesg(LABEL_DOES_NOT_EXIST, line_idx));
	return (1);
}

static int	get_label(t_asm *champ, t_token *token, char *value, int line_idx)
{
	int		i;

	i = -1;
	while (value[++i] && ft_strchr(LABEL_CHARS, value[i]))
		;
	if (value[i] && !(i == (int)(ft_strlen(value) - 1) && value[i] == LABEL_CHAR))
		return (err_mesg(BAD_CHARACTER_IN_LABEL, line_idx));
	if (value[i - 1] != LABEL_CHAR || ft_strlen(value) < 2)
		return (err_mesg(BAD_LABEL_FORMAT, line_idx));
	token->value = ft_strsub(value, 0, ft_strlen(value - 1));
	token->type = LABEL;
	if (label_exists(token->value, champ))
		return (err_mesg(DUPLICATE_VALUE, line_idx));
	return (1);
}

int			token_with_value(t_asm *champ, t_token *token, char *value, int line_idx)
{
	if (is_instruction(value))
	{
		token->value = ft_strdup(value);
		token->type = INSTRUCTION;
		return (1);
	}
	if (ft_strchr(value, DIRECT_CHAR) == value)
		return (get_direct_value(champ, token, value, line_idx));
	if (ft_strchr(value, LABEL_CHAR) && ft_strchr(value, LABEL_CHAR) != value)
	{
		return (get_label(champ, token, value, line_idx));
	}
	return (get_indirect_value(champ, token, value, line_idx));
}
