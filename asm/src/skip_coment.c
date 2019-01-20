/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_coment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:27:10 by pzakala           #+#    #+#             */
/*   Updated: 2019/01/19 15:27:31 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	skip_coment(char **code, int *i, int *j)
{
	*j = -1;
	while (code[(*i)] &&
		(code[*i][0] == COMMENT_CHAR || code[*i][0] == 0))
		(*i)++;
	if (!code[*i])
		return (err_mesg(NO_NAME_AND_NO_COMMENT, *i));
	while (ft_isspace(code[*i][++(*j)]))
		;
	if (code[*i][*j] != '.')
		return (err_mesg(INCORRECT_FIRST_LINE, *i));
	return (1);
}
