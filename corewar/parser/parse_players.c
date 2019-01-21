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

int		check_n_flag(int ac, char *av[], int *i)
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

int		read_champ(char *file, uint8_t *champ)
{
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit_func("File open error");
	if ((ret = read(fd, champ, MAX_READ + 1)) < 0)
		exit_func("File read error");
	if (ret < MIN_READ || ret > MAX_READ)
		exit_func("Champ size error");
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
		if (!check_flags(ac, av, &i))
			break ;
		if (++j == MAX_PLAYERS)
			exit_func("Too many players");
		champs[j].id = check_n_flag(ac, av, &i);
		champs[j].alive = 0;
		ret = read_champ(av[i], champ);
		check_magic(champ);
		get_name(&champs[j], &champ[4]);
		get_size(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4]);
		get_comment(&champs[j], &champ[4 + PROG_NAME_LENGTH + 4 + 4]);
		get_code(&champs[j], &champ[ON_CODE], ret, champ);
		i++;
	}
	champs[j + 1].id = -1;
	return (set_players_id(champs));
}
