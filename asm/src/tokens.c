/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:40:18 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/10 11:40:19 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			get_tokens(char **code, t_asm *champ)
{
	int		i;
	int		j;

	i = -1;
	if (!get_name_and_comment(code, champ, &i))
		return (0);
}