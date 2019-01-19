/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:40:18 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:24:40 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			unknown_character(char c)
{
	return (!ft_isspace(c) && !ft_strchr(LABEL_CHARS, c) &&
			c != LABEL_CHAR && c != DIRECT_CHAR &&
			c != SEPARATOR_CHAR && c != '-');
}

static int	split_line_into_tokens(char **code, t_asm *champ, int i)
{
	int		j;

	j = -1;
	while (code[i][++j])
	{
		if (code[i][j] == COMMENT_CHAR)
			return (1);
		if (unknown_character(code[i][j]))
			return (err_mesg(UNKNOWN_CHARACTER, i));
		if (!ft_isspace(code[i][j]))
			if (!add_token(code[i], i, &j, champ))
				return (0);
	}
	return (1);
}

int			get_tokens(char **code, t_asm *champ)
{
	int		i;

	i = -1;
	if (!get_name_and_comment(code, champ, &i))
		return (0);
	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return (err_mesg(TOO_LONG_CHAMPION_NAME, 0));
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		return (err_mesg(TOO_LONG_COMMENT, 0));
	while (code[i])
	{
		if (!split_line_into_tokens(code, champ, i))
			return (0);
		i++;
	}
	return (1);
}
