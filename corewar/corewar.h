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
# define MOST_LEFT_BIT 2147483648

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

typedef struct	s_cell
{
	uint8_t		v;
	int			id;
}				t_cell;

extern t_player	*g_players;
extern t_car	*g_carriage;


/*
**	Battle
*/

void			check_battle(t_car *car);
void			check_cars(t_car *car);

/*
**	Get values
*/

uint8_t			get_reg_num(t_cell *arena, t_car *car, int arg_num);
int				get_op_data(t_cell *arena, t_car *car);
int				get_ind(t_cell *arena, t_car *car, int arg_num, int size);
int				get_value(t_cell *arena, int start, int size);

/*
**	Utils
*/

void			skip_op(t_cell *arena, t_car *car);
int				to_arg(t_cell *arena, t_car *car, int arg_num);
void			put_on_arena(t_cell *arena, int start, uint8_t *val, int size);

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
t_cell			*init_battlefield(t_player *champs);

/*
**	Operations
*/

void			live_op(t_cell *arena, t_car *car);
void			ld_op(t_cell *arena, t_car *car);
void			st_op(t_cell *arena, t_car *car);
void			add_sub_op(t_cell *arena, t_car *car);
void			and_or_xor_op(t_cell *arena, t_car *car);
void			zjmp_op(t_cell *arena, t_car *car);
void			ldi_op(t_cell *arena, t_car *car);
void			sti_op(t_cell *arena, t_car *car);
void			fork_op(t_cell *arena, t_car *car);
void			aff_op(t_cell *arena, t_car *car);

static void		(*f_opers[17])() = {0, &live_op, &ld_op, &st_op, &add_sub_op, &add_sub_op, &and_or_xor_op, &and_or_xor_op, &and_or_xor_op, &zjmp_op, &ldi_op, &sti_op, &fork_op, &ld_op, &ldi_op, &fork_op, &aff_op};

/*
**	Tests
*/

void			print_players(t_player *champs);
void			print_cars(t_car *carriage);
void			putfile_hex(int ret, t_cell *file, int space, int newline);
void			putbyte_hex(uint8_t n);
void			putbytes_bit(char *n, int size);
void			print_args_type(t_car *car);
void			print_oper_data(t_cell *arena, t_car *car);

#endif
