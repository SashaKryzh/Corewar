/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:59:28 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/20 12:21:11 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	transform_name(t_asm *champ)
{
	char	*name;
	int		i;
	int		j;

	name = ft_strnew(PROG_NAME_LENGTH);
	i = -1;
	j = -1;
	while (champ->name[++j])
	{
		name[++i] = champ->name[j];
	}
	ft_strdel(&champ->name);
	champ->name = name;
}

static void	transform_comment(t_asm *champ)
{
	char	*comment;
	int		i;
	int		j;

	comment = ft_strnew(COMMENT_LENGTH);
	i = -1;
	j = -1;
	while (champ->comment[++j])
	{
		comment[++i] = champ->comment[j];
	}
	ft_strdel(&champ->comment);
	champ->comment = comment;
}

static int	write_null(t_asm *champ)
{
	char	*str;

	str = ft_strnew(3);
	return (write_to_file(champ, &str, 4));
}

static void	write_everything(t_asm *champ, char *filename)
{
	transform_name(champ);
	transform_comment(champ);
	get_size(champ);
	if (!get_code(champ) ||
		!write_magic(champ) ||
		!write_to_file(champ, &champ->name, PROG_NAME_LENGTH) ||
		!write_null(champ) ||
		!write_size(champ) ||
		!write_to_file(champ, &champ->comment, COMMENT_LENGTH) ||
		!write_null(champ) ||
		!write_to_file(champ, &champ->code, champ->size))
		return ;
	ft_putstr("\033[1;32mWriting output program to ");
	ft_putendl(filename);
	ft_putstr("\033[0m");
}

void		compile(char **code, char *filename)
{
	t_asm	champ;

	champ.tokens = NULL;
	champ.code = NULL;
	champ.labels = NULL;
	champ.name = NULL;
	champ.comment = NULL;
	if (!get_tokens(code, &champ))
	{
		delete_champ(&champ);
		return ;
	}
	if ((champ.fd = open(filename, O_RDWR | O_TRUNC |
		O_CREAT, 0666)) < 0)
	{
		delete_champ(&champ);
		return (perror("Error: "));
	}
	write_everything(&champ, filename);
	delete_champ(&champ);
}
