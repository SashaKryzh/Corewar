/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:42:45 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 17:10:30 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	incorrect_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 2)
		return (0);
	return (filename[len - 1] == 's' &&
			filename[len - 2] == '.');
}

void		work_with_file(char *filename)
{
	int		new_fd;
	int		fd;
	int		i;
	char	*new_name;

	if (!incorrect_file(filename))
		return ;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("ERROR");
	new_name = ft_strnew(ft_strlen(filename) + 2);
	i = -1;
	while (filename[++i])
		new_name[i] = filename[i];
	new_name[i - 1] = 'c';
	new_name[i] = 'o';
	new_name[i + 1] = 'r';
	if ((new_fd = open(new_name, O_RDWR | O_TRUNC |
		O_CREAT, 0666)) < 0)
		return (perror("Error: "));
	write_nbr(new_fd, COREWAR_EXEC_MAGIC);
	comands(fd, new_fd, &i);
	compile_code(fd, new_fd);
	close(new_fd);
}
