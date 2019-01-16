/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_indirect_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 12:00:51 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 16:15:01 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	get_label(t_token *token, char *value, int line_idx)
{
	int		i;

	i = 0;
	while (value[++i] && ft_strchr(LABEL_CHARS, value[i]))
		;
	if (value[i])
		return (err_mesg(BAD_CHARACTER_IN_LABEL, line_idx));
	token->value = ft_strsub(value, 1, ft_strlen(value) - 1);
	token->type = INDIRECT_LABEL;
	return (1);
}

static int	get_registry(t_token *token, char *value, int line_idx)
{
	int		i;
	int		reg;

	reg = 0;
	i = 0;
	while (value[++i] && ft_isdigit(value[i]))
		reg = reg * 10 + value[i] - '0';
	if (value[i])
		return (err_mesg(BAD_CHARACTER_IN_REGISTER, line_idx));
	if (reg > 99 || !reg)
		return (err_mesg(BAD_REGISTER_IDX, line_idx));
	token->type = REGISTER;
	token->value = ft_strsub(value, 1, ft_strlen(value) - 1);
	return (1);
}

int			get_indirect_value(t_token *token,
		char *value, int line_idx)
{
	int		i;

	if (value[0] == LABEL_CHAR)
		return (get_label(token, value, line_idx));
	if (value[0] == 'r')
		return (get_registry(token, value, line_idx));
	i = -1;
	if (value[0] == '-')
		++i;
	while (value[++i] && ft_isdigit(value[i]))
		;
	if (value[i])
		return (err_mesg(BAD_CHARACTER_IN_INDIRECT_VALUE, line_idx));
	token->type = INDIRECT_VALUE;
	token->value = ft_strdup(value);
	return (1);
}
