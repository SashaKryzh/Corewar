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

int		check_flag(int ac, char *av[], int *i)
{
	int	id;

	if (ft_strequ(av[*i], "-n"))
	{
		if (*i + 2 >= ac)
		{
			ft_printf("n flag error\n");
			exit(0);
		}
		*i += 2;
		if ((id = ft_atoi(av[*i - 1])) < 1 || id > MAX_PLAYERS)
		{
			ft_printf("n < 1\n");
			exit(0);
		}
		return (id);
	}
	return (MAX_PLAYERS + 1);
}

void	sort_players_id(t_player *champs)
{
	t_player	tmp;
	int			i;
	int			j;

	i = 0;
	while (champs[i + 1].id != -1)
	{
		j = 0;
		while (champs[j + 1]. id != -1)
		{
			if (champs[j].id > champs[j + 1].id)
			{
				tmp = champs[j];
				champs[j] = champs[j + 1];
				champs[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int 	free_id(t_player *champs)
{
	int id;
	int	j;
	int	ret;

	id = 1;
	while (id != MAX_PLAYERS + 1)
	{
		j = 0;
		ret = 1;
		while (champs[j].id != -1)
		{
			if (champs[j].id == id)
				ret = 0;
			j++;
		}
		if (ret)
			return (id);
		id++;
	}
	ft_printf("bad id\n");
	exit(0);
}

void	set_players_id(t_player *champs)
{
	int i;

	i = 0;
	if (champs[0].id == -1)
	{
		ft_printf("no players\n");
		exit(0);
	}
	while (champs[i].id != -1)
	{
		if (champs[i].id == MAX_PLAYERS + 1)
			champs[i].id = free_id(champs);
		i++;
	}
	sort_players_id(champs);
	i = 0;
	while (champs[i + 1].id != -1)
	{
		if (champs[i].id == champs[i + 1].id)
		{
			ft_printf("same id\n");
			exit(0);
		}
		i++;
	}
}

void	parse_players(t_player *champs, int ac, char *av[])
{
	uint8_t			champ[5000];
	int				ret;
	int				i;
	int				j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		champs[j].id = check_flag(ac, av, &i);
		ret = read_champ(av[i], champ);
		putfile(ret, champ);
		check_magic(champ);
		get_name(&champs[j], &champ[4]);
		get_size(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4]);
		get_comment(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4]);
		get_code(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4], ret, champ);
		i++;
		if (++j == MAX_PLAYERS)
		{
			ft_printf("Too many players\n");
			exit(0);
		}
	}
	champs[j].id = -1;
	set_players_id(champs);
}

int		main(int ac, char *av[])
{
	t_player		champs[MAX_PLAYERS + 1];

	parse_players(champs, ac, av);
	print_players(champs); //
	return (0);
}
