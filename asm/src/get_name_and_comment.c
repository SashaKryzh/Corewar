/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:43:04 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/10 12:43:05 by amoroziu         ###   ########.fr       */
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

static int 	check_rest(char *str, int start)
{
	while (str[++start])
		if (str[start] == COMMENT_CHAR)
			return (1);
		else if (!ft_isspace(str[start]))
			return (0);
	return (1);
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
		return (get_multiline_string(str, code, &((*i++))));
	}
	else
	{
		temp = ft_strsub(code[*i], 0, j);
		*str = freejoin(*str, temp);
		free(temp);
		return (check_rest(code[i], j));
	}
}

static int	get_string(char **code, char **str, int *i)
{
	int		j;
	int		len;

	j = 4;
	while (ft_isspace(code[*i][++j]))
		;
	if (!code[*i][j] || code[*i][j] != '"')
		return (err_mesg(NO_NAME));
	len = 0;
	while (code[*i][j + ++len] && code[*i][j + len] != '"')
		;
	if (!code[j + len])
	{
		*str = ft_strsub(code[*i], j, len - 1);
		return (get_multiline_string(str, code, &((*i)++)));
	}
	else
		*str = ft_strsub(code[*i], j, len);
	(*i)++;
	return (1);
}

int			get_name_and_comment(char **code, t_asm *champ, int *i)
{
	while (code[++(*i)] && code[*i][0] == COMMENT_CHAR)
		;
	if (!code[*i])
		return (err_mesg(NO_NAME_AND_NO_COMMENT));
	if (code[*i][0] != '.')
		return (err_mesg(INCORRECT_FIRST_LINE));
	if (ft_strnequ(".name", code[*i], 5) && ft_isspace(code[*i][5]))
		return (get_string(code, &champ->name, *i) && get_string(code, &champ->comment, *i));
	else if (ft_strnequ(".comment", code[*i], 8) && ft_isspace(code[*i][8]))
		return (get_string(code, &champ->comment, *i) && get_string(code, &champ->name, *i));
	else
		return (err_mesg(INCORRECT_FIRST_LINE));
}