/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 21:54:37 by pzakala           #+#    #+#             */
/*   Updated: 2019/01/17 21:58:59 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	transform_str(int fd, char *str, size_t len, int *i)
{
	size_t		size;

	size = ft_strlen(str);
	if (size > len)
		error_m("Too long string!", fd, *i);
	write_to_file_com(fd, str, size);
	while (size < len)
	{
		write(fd, "\0", 1);
		size++;
	}
	write_nbr(fd, 0);
	if (len == PROG_NAME_LENGTH)
		write_nbr(fd, CHAMP_MAX_SIZE);
}

static char *read_comand(int fd, int n_fd, int *i)
{
	char *str;
	char buff[2];
	char *save;

	str = (char *)malloc(1);
	buff[1] = 0;
	while (read(fd, buff, 1) > 0 && ft_isspace(*buff))
		if (*buff == '\n')
			(*i)++;
	if (*buff != '"')
		error_m("String not found!", n_fd, *i);
	while (read(fd, buff, 1) > 0 && *buff != '"')
	{
		save = str;
		str = ft_strjoin(str, buff);
		free(save);
		if (*buff == '\n')
			(*i)++;
	}
	return (str);
}

static void	find_coment(int fd, int *i)
{
	char	buff[1];

	while (read(fd, buff, 1) > 0 && *buff != '.')
		if (*buff == '\n')
			(*i)++;
		else if (*buff == '#')
		{
			while (read(fd, buff, 1) > 0 && *buff && *buff != '\n')
				;
			(*i)++;
		}
}

static int	find_command(int fd, int n_fd, int *i)
{
	char	buff[8];
	int		j;

	j = -1;
	ft_bzero(buff, 8);
	find_coment(fd, i);
	if (read(fd, buff, 1) > 0 && *buff == 'n')
	{
		if (read(fd, buff, 4) > 0 && ft_strequ("ame ", buff))
			return (1);
		while (++j < 4)
				*i += (buff[j] == '\n' ? 1 : 0);
		error_m("Comand not found!", n_fd, *i);
	}
	else if (*buff == 'c')
	{
		if (read(fd, buff, 7) > 0 && ft_strequ("omment ", buff))
			return (2);
		while (++j < 7)
			*i += (buff[j] == '\n' ? 1 : 0);
		error_m("Comand not found!", n_fd, *i);
	}
	return (error_m("No comands!", n_fd, *i));
}

void 		comands(int fd, int n_fd, int *i)
{
	char	*str;

	*i = 1;
	if (find_command(fd, n_fd, i) == 1)
	{
		transform_str(n_fd, read_comand(fd, n_fd, i), PROG_NAME_LENGTH, i);
		if (find_command(fd, n_fd, i) == 1)
			error_m("Champion have two names!", n_fd, *i);
		else
			transform_str(n_fd, read_comand(fd, n_fd, i), COMMENT_LENGTH, i);
	}
	else
	{
		str = read_comand(fd, n_fd, i);
		if (find_command(fd, n_fd, i) == 1)
		{
			transform_str(n_fd, read_comand(fd, n_fd, i), PROG_NAME_LENGTH, i);
			transform_str(n_fd, str, COMMENT_LENGTH, i);
		}
		else
			error_m("Champion have two comments!", n_fd, *i);
	}
}
