/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:40:18 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 16:12:54 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			unknown_character(char c)
{
	return (!ft_isspace(c) && !ft_strchr(LABEL_CHARS, c) &&
			c != LABEL_CHAR && c != DIRECT_CHAR &&
			c != SEPARATOR_CHAR && c != '-');
}

static int	split_line_into_tokens(char **code, t_asm *champ, int i)
{
	int		j;

	j = -1;
	while (code[i][++j])
	{
		if (code[i][j] == COMMENT_CHAR)
			return (1);
		if (unknown_character(code[i][j]))
			return (err_mesg(UNKNOWN_CHARACTER, i));
		if (!ft_isspace(code[i][j]))
			if(!add_token(code[i], i, &j, champ))
				return (0);
	}
	return (1);
}

static void	expand_arr(char ***arr, char *line)
{
	int		i;

	i = -1;
	while ((*arr)[++i])
		;
	*arr = (char**)realloc((void*)(*arr), sizeof(char*) * (i + 2));
	(*arr)[i] = line;
	(*arr)[i + 1] = NULL;
}

static char	**read_file(const int fd)
{
	char	*line;
	char	**content;

	content = (char**)malloc(sizeof(char*));
	content[0] = NULL;
	while (get_next_line(fd, &line))
		expand_arr(&content, line);
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
	free(line);
	return (content);
}

void		print_arm(t_asm *champ)  //DELETE
{
	t_token *t;
	t_label *lb;
	t_missed_label *ml;

	ft_putendl(champ->code);
	ft_printf("%d %d %d\n", champ->cur_pos, champ->written_bytes, champ->fd);
	t = champ->tokens;
	ft_putendl("t");
	while (t)
	{
		ft_printf("%d %s %d\n", t->type, t->value, t->line);
		t = t->next;
	}
	ft_putendl("lb");
	lb = champ->labels;
	while (lb)
	{
		ft_printf("%s %s\n", lb->label_name, lb->code_pos);
		lb = lb->next;
	}
	ft_putendl("ml");
	ml = champ->missed_labels;
	while (ml)
	{
		ft_printf("%d %s %s\n", ml->size, ml->label_name, ml->code_pos);
		ml = ml->next;
	}
}

int			compile_code(int fd, int n_fd)
{
	int		i;
	char	**code;
	t_asm	champ;

	i = -1;
	champ.tokens = NULL;
	champ.code = NULL;
	champ.labels = NULL;
	champ.missed_labels = NULL;
	champ.fd = n_fd;
	if (!(code = read_file(fd)))
		return (0);
	while (code[++i])
	{
	    ft_printf("|%s|\n", code[i]);
		if (!split_line_into_tokens(code, &champ, i))
			return (0);
	}
	print_arm(&champ);
	if (!get_code(&champ) ||
		write_to_file(&champ, champ.code))
		return (0);
	return (1);
}
