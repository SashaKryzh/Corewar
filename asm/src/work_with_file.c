/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:42:45 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/09 13:42:47 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	incorrect_file(char *filename)
{
	return (filename[ft_strlen(filename)] == 's' &&
			filename[ft_strlen(filename) - 1] == '.');
}

static void	expand_arr(char **arr, char *line)
{
	int		i;

	i = -1;
	while (arr[++i])
		;
	arr = (char**)realloc(sizeof(char*) * (i + 2));
	arr[i] = line;
	arr[i + 1] = NULL;
}

static char	**read_file(const int fd)
{
	char	*line;
	char	**content;
	int		i;

	lseek(fd, -1, SEEK_END);
	line = (char*)malloc(sizeof(char));
	if (read(fd, line, 1) == -1)
	{
		perror("ERROR");
		return (NULL);
	}
	if (line[0] != '\n')
	{
		free(line);
		return (NULL);
	}
	lseek(fd, 0, SEEK_START);
	free(line);
	content = (char**)malloc(sizeof(char*));
	content[0] = NULL;
	while (get_next_line(fd, &line))
		expand_arr(content, line);
	return (content);
}

void		work_with_file(char *filename)
{
	int		fd;
	int		i;
	char	**content;
	char	*new_name;

	if (incorrect_file(filename))
		return ;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("ERROR");
	if (!(content = read_file(fd)))
		return ;
	new_name = ft_strnew(ft_strlen(filename) + 2);
	i = -1;
	while (filename[++i])
		new_name[i] = filename[i];
	new_name[i - 1] = 'c';
	new_name[i] = 'o';
	new_name[i + 1] = 'r';
	compile(content, filename)
}