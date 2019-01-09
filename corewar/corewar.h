/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 08:32:17 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/08 08:32:17 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdint.h>

# include "op.h"

typedef struct	s_player
{
	int			id;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	int			code_size;
	uint8_t		*code;
}				t_player;

typedef struct	s_carriage
{
	int			id;
	t_bool		carry;
	int			last_live;
	int			remain_cycles;
	int			position;
	int			to_jump;
	uint8_t		regs[REG_NUMBER];
}				t_carriage;

/*
**	Parser
*/

int				parse_players(t_player *champs, int ac, char *av[]);

void			get_name(t_player *champs, uint8_t *champ);
void			get_size(t_player *champs, uint8_t *champ);
void			get_comment(t_player *champs, uint8_t *champ);
void			get_code(t_player *champs, uint8_t *champ, int ret, uint8_t *start);

void			check_null(uint8_t	*champ);
void			check_magic(uint8_t *champ);

int				set_players_id(t_player *champs);

/*
**	Utils
*/

void			exit_func(char *msg);

/*
**	Tests
*/

void			print_players(t_player *champs);
void			putfile_hex(int ret, uint8_t *file, int space, int newline);

#endif
