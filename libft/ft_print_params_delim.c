/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params_delim.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 08:00:25 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/29 08:00:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_params_delim(int ac, char **av, char *delim)
{
	int i;

	if (ac == 1)
		return ;
	i = 1;
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i + 1 != ac)
			ft_putstr(delim);
		else
			ft_putchar('\n');
		i++;
	}
}
