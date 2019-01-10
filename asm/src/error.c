/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:58:58 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/10 11:59:04 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		err_mesg(int err_code)
{
	if (err_code == NO_NAME)
		ft_putendl_fd("ERROR: No champion name given!", 2);
	else if (err_code == NO_COMMENT)
		ft_putendl_fd("ERROR: No comment given!", 2);
	else if (err_code == NO_NAME_AND_NO_COMMENT)
		ft_putendl_fd("ERROR: No champion name and no comment given!", 2);
	else if (err_code == INCORRECT_FIRST_LINE)
		ft_putendl_fd("ERROR: First line must be champion's name or comment!", 2);
	return (0);
}