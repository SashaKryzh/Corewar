/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:59:28 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/15 15:40:22 by amoroziu         ###   ########.fr       */
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
	while (++i < PROG_NAME_LENGTH)
		name[i] = '0';
	i = -1;
	j = -1;
	while (champ->name[++j])
	{
		name[++i] = champ->name[j] / 16 + '0';
		name[++i] = champ->name[j] % 16 + '0';
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
	while (++i < COMMENT_LENGTH)
		comment[i] = '0';
	i = -1;
	j = -1;
	while (champ->comment[++j])
	{
		comment[++i] = champ->comment[j] / 16 + '0';
		comment[++i] = champ->comment[j] % 16 + '0';
	}
	ft_strdel(&champ->comment);
	champ->comment = comment;
}

static int	write_size(t_asm *champ)
{
	int		size;

	size = ft_strlen(champ->code);
	write_to_file(champ, int_to_hex(size, 4));
	return (1);
}

void		compile(char **code, char *filename)
{
	t_asm	champ;

	champ.tokens = NULL;
	champ.code = NULL;
	champ.labels = NULL;
	champ.missed_labels = NULL;
	if (!get_tokens(code, &champ))
		return ;
	if ((champ.fd = open(filename, O_WRONLY | O_CREAT)) < 0)
		return (perror("Error: "));
	transform_name(&champ);
	transform_comment(&champ);
	if (!get_code(&champ) ||
		!write_magic(&champ) ||
		!write_to_file(&champ, champ.name) ||
		!write_to_file(&champ, ft_strdup("00000000")) ||
		!write_size(&champ) ||
		!write_to_file(&champ, champ.comment) ||
		!write_to_file(&champ, ft_strdup("00000000")) ||
		!write_to_file(&champ, champ.code))
		return ;
}
