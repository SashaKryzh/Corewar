/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:16:00 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 15:16:00 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	check_null(uint8_t *champ)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (champ[i] != 0)
			exit_func("Null error");
		i++;
	}
}

void	check_magic(uint8_t *champ)
{
	int			magic;

	ft_memcpy(&magic, champ, 4);
	ft_memrev(&magic, 4);
	if (magic != COREWAR_EXEC_MAGIC)
		exit_func("MAGIC ERROR\n");
}
