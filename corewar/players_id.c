/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 18:46:38 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 18:46:38 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	sort_players_id(t_player *champs)
{
	t_player	tmp;
	int			i;
	int			j;

	i = 0;
	while (champs[i + 1].id != -1)
	{
		j = 0;
		while (champs[j + 1].id != -1)
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

int		free_id(t_player *champs)
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
	exit_func("Bad id");
	return (-1);
}

int		set_players_id(t_player *champs)
{
	int i;

	i = 0;
	if (champs[0].id == -1)
		exit_func("No players");
	while (champs[i].id != -1)
	{
		if (champs[i].id == MAX_PLAYERS + 1)
			champs[i].id = free_id(champs);
		i++;
	}
	sort_players_id(champs);
	i = 0;
	while (champs[i].id != -1)
	{
		if (champs[i + 1].id != -1 && champs[i].id == champs[i + 1].id)
			exit_func("Same id");
		if (champs[i].id != i + 1)
			exit_func("Invalid id");
		i++;
	}
	return (i);
}
