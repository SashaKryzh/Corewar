/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 12:50:29 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 11:33:14 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			write_to_file(t_asm *champ, char *line)
{
	int		ws;

	ws = ft_strlen(line);
	if (write(champ->fd, line, ws) < 0)
	{
		perror("Error ");
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

int			write_to_file_com(int fd, char *line, int len)
{
	if (write(fd, line, len) < 0)
	{
		perror("Error ");
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

int			write_nbr(int fd, int magic)
{
	char	*str;
	int		i;

	i = 4;
	str = ft_strnew(i);
	while (--i >= 0)
	{
		str[i] = magic % 256;
		magic /= 256;
	}
	return (write_to_file_com(fd, str, 4));
}
