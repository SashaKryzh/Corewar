/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:56:11 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/03 15:56:13 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_update_str(int path, char *st_buff, char *buff, size_t len)
{
	char *tmp;

	tmp = st_buff;
	if (path == 1)
		st_buff = ft_strjoin(st_buff, buff);
	else if (path == 2)
		st_buff = ft_strdup(&st_buff[len + 1]);
	free(tmp);
	return (st_buff);
}

static int		ft_return_line(int ret, char **st_buff, int fd, char **line)
{
	size_t	len;

	len = 0;
	while (st_buff[fd][len] != '\n' && st_buff[fd][len] != '\0')
		len++;
	if (st_buff[fd][len] == '\n')
	{
		*line = len ? ft_strsub(st_buff[fd], 0, len) : ft_strnew(0);
		st_buff[fd] = ft_update_str(2, st_buff[fd], NULL, len);
		if (st_buff[fd][0] == '\0')
			ft_strdel(&st_buff[fd]);
	}
	else
	{
		*line = len ? ft_strsub(st_buff[fd], 0, len) : NULL;
		ft_strdel(&st_buff[fd]);
		if (*line == NULL && ret == 0)
			return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*st_buff[MAX_FD_CNT];
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	st_buff[fd] = st_buff[fd] ? st_buff[fd] : ft_strnew(0);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		st_buff[fd] = ft_update_str(1, st_buff[fd], buff, 0);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	return (ft_return_line(ret, st_buff, fd, line));
}
