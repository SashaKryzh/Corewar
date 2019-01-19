/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 12:50:29 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:04:16 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			write_to_file(t_asm *champ, char **line, int size)
{
	if (write(champ->fd, *line, size) < 0)
	{
		perror("Error ");
		return (0);
	}
	ft_strdel(line);
	return (1);
}

int			write_magic(t_asm *champ)
{
	int		magic;
	char	*str;
	int		i;

	str = ft_strnew(4);
	magic = COREWAR_EXEC_MAGIC;
	i = 4;
	while (--i >= 0)
	{
		str[i] = magic % 256;
		magic /= 256;
	}
	return (write_to_file(champ, &str, 4));
}

int			write_size(t_asm *champ)
{
	char	*size;
	int		i;
	int		temp;

	size = ft_strnew(4);
	temp = champ->size;
	i = 4;
	while (--i >= 0)
	{
		size[i] = temp % 256;
		temp /= 256;
	}
	return (write_to_file(champ, &size, 4));
}
