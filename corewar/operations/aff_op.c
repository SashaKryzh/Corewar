/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:22:12 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/14 19:22:13 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	aff_op(t_cell *arena, t_car *car)
{
	int reg_num;

	reg_num = get_reg_num(arena, car, 1);
	ft_printf("Aff: %c\n", (char)(car->regs[reg_num - 1]));
}
