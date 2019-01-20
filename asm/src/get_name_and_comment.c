/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:43:04 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 12:31:07 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char	*freejoin(char *s1, char *s2)
{
	char	*temp;

	temp = s1;
	s1 = ft_strjoin(s1, s2);
	free(temp);
	return (s1);
}

static int	get_multiline_string(char **str, char **code, int *i)
{
	int		j;
	char	*temp;

	j = -1;
	while (code[*i][++j] && code[*i][j] != '"')
		;
	*str = freejoin(*str, "\n");
	if (!code[*i][j])
	{
		*str = freejoin(*str, code[*i]);
		(*i)++;
		return (get_multiline_string(str, code, i));
	}
	else
	{
		temp = ft_strsub(code[*i], 0, j);
		*str = freejoin(*str, temp);
		free(temp);
		return (check_rest(code[(*i)++], j));
	}
}

static int	get_name(char **code, t_asm *champ, int *i, int j)
{
	int		len;
	char	*str;

	j += 4;
	while (ft_isspace(code[*i][++j]))
		;
	if (!code[*i][j] || code[*i][j] != '"')
		return (err_mesg(NO_NAME, *i));
	len = 0;
	while (code[*i][j + ++len] && code[*i][j + len] != '"')
		;
	if (!code[*i][j + len])
	{
		str = ft_strsub(code[*i], j + 1, len - 1);
		champ->name = str;
		(*i)++;
		return (get_multiline_string(&champ->name, code, i));
	}
	else
		str = ft_strsub(code[*i], j + 1, len - 1);
	(*i)++;
	champ->name = str;
	return (1);
}

static int	get_comment(char **code, t_asm *champ, int *i, int j)
{
	int		len;
	char	*str;

	j += 7;
	while (ft_isspace(code[*i][++j]))
		;
	if (!code[*i][j] || code[*i][j] != '"')
		return (err_mesg(NO_COMMENT, *i));
	len = 0;
	while (code[*i][j + ++len] && code[*i][j + len] != '"')
		;
	if (!code[*i][j + len])
	{
		str = ft_strsub(code[*i], j + 1, len - 1);
		champ->comment = str;
		(*i)++;
		return (get_multiline_string(&champ->comment, code, i));
	}
	else
		str = ft_strsub(code[*i], j + 1, len - 1);
	(*i)++;
	champ->comment = str;
	return (1);
}

int			get_name_and_comment(char **code, t_asm *champ, int *i)
{
	int	j;

	j = -1;
	while (code[++(*i)] &&
		(code[*i][0] == COMMENT_CHAR || code[*i][0] == 0))
		;
	if (!code[*i])
		return (err_mesg(NO_NAME_AND_NO_COMMENT, *i));
	while (ft_isspace(code[*i][++j]))
		;
	if (code[*i][j] != '.')
		return (err_mesg(INCORRECT_FIRST_LINE, *i));
	if (ft_strnequ(".name", code[*i] + j, 5))
		return (get_name(code, champ, i, j) &&
				skip_coment(code, i, &j) &&
				get_comment(code, champ, i, j));
	else if (ft_strnequ(".comment", code[*i] + j, 8))
		return (get_comment(code, champ, i, j) &&
				skip_coment(code, i, &j) &&
				get_name(code, champ, i, j));
	else
		return (err_mesg(INCORRECT_FIRST_LINE, *i));
}
