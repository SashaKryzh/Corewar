/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:34:15 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:47:38 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		main(int argc, char **argv)
{
	int		i;

	if (argc == 1)
		ft_putendl("usage: ./asm file1.c file2.c ...");
	else
	{
		i = 0;
		while (++i < argc)
			work_with_file(argv[i]);
	}
	return (0);
}
