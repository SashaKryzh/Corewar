/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:05:03 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/09 14:05:03 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		check_flag(int ac, char *av[], int *i)
{
	int	id;

	if (ft_strequ(av[*i], "-n"))
	{
		if (*i + 2 >= ac)
			exit_func("-n error");
		*i += 2;
		if ((id = ft_atoi(av[*i - 1])) < 1 || id > MAX_PLAYERS)
			exit_func("Unreal id");
		return (id);
	}
	return (MAX_PLAYERS + 1);
}

int		read_champ(char *file, unsigned char *champ)
{
	int		fd;
	int		ret;
	int		max_read;
	int		min_read;

	min_read = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	max_read = min_read + CHAMP_MAX_SIZE;
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_func("Invalid file");
	ret = read(fd, champ, max_read + 1);
	if (ret < min_read || ret > max_read)
		ft_printf("SIZE ERROR\n");
	close(fd);
	return (ret);
}

/*
**	Return number of players
*/

int		parse_players(t_player *champs, int ac, char *av[])
{
	uint8_t			champ[5000];
	int				ret;
	int				i;
	int				j;

	i = 1;
	j = -1;
	while (i < ac)
	{
		if (++j == MAX_PLAYERS)
			exit_func("Too many players");
		champs[j].id = check_flag(ac, av, &i);
		champs[j].alive = 0;
		ret = read_champ(av[i], champ);
		// putfile_hex(ret, champ);
		check_magic(champ);
		get_name(&champs[j], &champ[4]);
		get_size(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4]);
		get_comment(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4]);
		get_code(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4], ret, champ);
		i++;
	}
	champs[j + 1].id = -1;
	return (set_players_id(champs));
}
