/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 12:50:29 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 16:08:06 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char	*insert_spaces(t_asm *champ, char *line)
{
	int		bytes;
	char	*new;
	int		i;
	int		j;

	bytes = (champ->written_bytes % 4 + ft_strlen(line)) / 4;
	new = ft_strnew(ft_strlen(line) + bytes);
	i = -1;
	j = 0;
	while (line[j])
	{
		if (((j + champ->written_bytes % 4) % 4) == 0)
			new[++i] = ' ';
		else
			new[++i] = line[j++];
	}
	ft_strdel(&line);
	return (new);
}

int			write_to_file(t_asm *champ, char *line)
{
	int		ws;

	ws = ft_strlen(line);
	line = insert_spaces(champ, line);
	if (write(champ->fd, line, ft_strlen(line)) < 0)
	{
		perror("Error ");
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

int			write_magic(t_asm *champ)
{
	int		magic;
	char	*str;
	int		i;

	str = ft_strnew(8);
	magic = COREWAR_EXEC_MAGIC;
	i = 8;
	while (--i >= 0)
	{
		str[i] = magic % 16;
		magic /= 16;
	}
	return (write_to_file(champ, str));
}

int			write_size(t_asm *champ)
{
	int		size;
	int		i;
	char	*hex;

	size = ft_strlen(champ->code) / 2;
	hex = ft_strnew(8);
	i = 8;
	while (--i >= 0)
	{
		hex[i] = size % 16;
		size /= 16;
	}
	return (write_to_file(champ, hex));
}
