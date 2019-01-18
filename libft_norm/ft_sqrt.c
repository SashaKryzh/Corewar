/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:37:10 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/27 16:37:11 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int	root;

	if (nb == 0)
		return (0);
	root = 1;
	while (root * root < nb)
		root++;
	if (root * root == nb)
		return (root);
	return (-1);
}
