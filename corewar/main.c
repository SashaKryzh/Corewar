/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 07:54:25 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 07:54:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		read_champ(char *file, unsigned char *champ)
{
	int		fd;
	int		ret;
	int		max_read;
	int		min_read;

	min_read = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	max_read = min_read + CHAMP_MAX_SIZE;
	fd = open(file, O_RDONLY);
	ret = read(fd, champ, max_read + 1);
	if (ret < min_read || ret > max_read)
		ft_printf("SIZE ERROR\n");
	close(fd);
	return (ret);
}

void	puthex(uint8_t n)
{
	char	buff[2];

	if (n % 16 > 9)
		buff[1] = (n % 16 - 10 + 'a');
	else
		buff[1] = (n % 16 + '0');
	n /= 16;
	if (n % 16 > 9)
		buff[0] = (n % 16 - 10 + 'a');
	else
		buff[0] = (n % 16 + '0');
	write(1, buff, 2);
}

void	putfile(int ret, uint8_t *file)
{
	for (int j = 0; j < ret; j++)
	{
		if (j != 0 && j % 16 == 0)
			ft_printf("\n");
		puthex(file[j]);
		if (j % 2 == 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	parse_players(t_player *champs, int ac, char *av[])
{
	int				i;
	int				j;
	int				ret;
	uint8_t			champ[5000];

	i = 1;
	j = 0;
	while (i < ac)
	{
		ret = read_champ(av[i], champ);
		putfile(ret, champ);
		check_magic(champ);
		get_name(&champs[j], &champ[4]);
		get_size(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4]);
		get_comment(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4]);
		get_code(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4], ret, champ);
		i++;
		j++;
	}
	champs[j].id = -1;
	print_players(champs);
}

int		main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];

	parse_players(champs, ac, av);
	return (0);
}
