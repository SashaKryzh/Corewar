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
# include <stdbool.h>

# include "op.h"

# define OP g_op[car->op - 1]

extern int	g_cnt_cars;
extern int	g_last_alive;
extern int	g_cnt_cycles;
extern int	g_cnt_live;
extern int	g_cycles_to_die;
extern int	g_cnt_checks;

typedef struct	s_player
{
	int					id;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					code_size;
	bool				alive;
	uint8_t				*code;
}				t_player;

typedef struct	s_carriage
{
	int					id;
	bool				carry;
	int					last_live;
	int					remain_cycles;
	int					position;
	int					no_jump;
	int					regs[REG_NUMBER];

	uint8_t				op;
	uint8_t				args_types[3];
	uint8_t				args_sizes[3];
	struct s_carriage	*next;
}				t_car;

extern t_player	*g_players;
extern t_car	*g_carriage;

/*
**	Get values
*/

uint8_t			get_reg_num(uint8_t *arena, t_car *car, int arg_num);

int				get_op_data(uint8_t *arena, t_car *car);

int				get_dir(uint8_t *arena, t_car *car, int start);
int				get_ind(uint8_t *arena, t_car *car, int start);

/*
**	Utils
*/

void			skip_op(uint8_t *arena, t_car *car);
int				to_arg(uint8_t *arena, t_car *car, int arg_num);
void			put_on_arena(uint8_t *arena, int start, uint8_t *val, int size);

/*
**	Parser
*/

int				parse_players(t_player *champs, int ac, char *av[]);

void			get_name(t_player *champs, uint8_t *champ);
void			get_size(t_player *champs, uint8_t *champ);
void			get_comment(t_player *champs, uint8_t *champ);
void			get_code(t_player *champs, uint8_t *champ,
				int ret, uint8_t *start);

void			check_null(uint8_t	*champ);
void			check_magic(uint8_t *champ);

int				set_players_id(t_player *champs);

/*
**	Utils 2
*/

void			exit_func(char *msg);
t_car			*init_cars(void);
uint8_t			*init_battlefield(t_player *champs);

/*
**	Operations
*/

void			live_op(uint8_t *arena, t_car *car);
void			ld_op(uint8_t *arena, t_car *car);
void			zjmp_op(uint8_t *arena, t_car *car);
void			sti_op(uint8_t *arena, t_car *car);
void			fork_op(uint8_t *arena, t_car *car);

/*
**	Tests
*/

void			print_players(t_player *champs);
void			print_cars(t_car *carriage);
void			putfile_hex(int ret, uint8_t *file, int space, int newline);
void			putbyte_hex(uint8_t n);
void			putbytes_bit(char *n, int size);
void			print_args_type(t_car *car);

#endif
