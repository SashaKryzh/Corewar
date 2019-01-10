/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:14:09 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 15:14:09 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	get_name(t_player *champs, uint8_t *champ)
{
	int	i;

	i = 0;
	while (i < PROG_NAME_LENGTH && champ[i])
	{
		champs->name[i] = champ[i];
		i++;
	}
	champs->name[i] = '\0';
	check_null(&champ[PROG_NAME_LENGTH]);
}

void	get_size(t_player *champs, uint8_t *champ)
{
	ft_memcpy(&champs->code_size, champ, 4);
	ft_memrev(&champs->code_size, 4);
	if (champs->code_size < 0 || champs->code_size > CHAMP_MAX_SIZE)
		ft_printf("CODE SIZE ERROR\n");
}

void	get_comment(t_player *champs, uint8_t *champ)
{
	int		i;

	i = 0;
	while (i < COMMENT_LENGTH && champ[i])
	{
		champs->comment[i] = champ[i];
		i++;
	}
	champs->comment[i] = '\0';
	check_null(&champ[COMMENT_LENGTH]);
}

void	get_code(t_player *champs, uint8_t *champ, int ret, uint8_t *start)
{
	int i;

	i = 0;
	champs->code = (uint8_t *)ft_memalloc(sizeof(uint8_t) * champs->code_size);
	while (i < champs->code_size && i < ret)
	{
		champs->code[i] = champ[i];
		i++;
	}
	if (&champ[i] - start != ret)
		ft_printf("CODE SIZE AND CODE HAVE DIFF SIZES\n");
}
