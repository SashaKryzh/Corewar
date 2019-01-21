/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 08:32:17 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 20:18:50 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

# include "op.h"

# define OP g_op[car->op - 1]
# define MOST_LEFT_BIT 2147483648

# define SHOW_CYCLES (g_debug & 2)
# define SHOW_OPERS (g_debug & 4)
# define OPER_INFO "P %4d | %s ", car->id, OP.name

# define ON_CODE 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4
# define MIN_READ (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
# define MAX_READ (MIN_READ + CHAMP_MAX_SIZE)

extern int	g_start_to_show;

extern int	g_visual;
extern int	g_debug;
extern int	g_format;
extern int	g_dump;

extern int	g_cnt_players;
extern int	g_cnt_cars;
extern int	g_last_alive;
extern int	g_cnt_cycles;
extern int	g_cnt_live;
extern int	g_cycles_to_die;

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
	int					position;
	int					no_jump;
	int					regs[REG_NUMBER];

	int					color;

	uint8_t				op;
	int					remain_cycles;
	uint8_t				args_types[3];
	uint8_t				args_sizes[3];

	struct s_carriage	*next;
}				t_car;

typedef struct	s_cell
{
	uint8_t		v;
	int			id;
}				t_cell;

extern t_player	g_players[MAX_PLAYERS + 1];
extern t_car	*g_carriage;

/*
**	Battle
*/

void			battle(t_cell *arena);
void			check_battle_status(t_cell *arena);
void			check_battle(void);
void			check_battle_2(int *cnt_cycles, int *changed);
void			check_cars(void);

/*
**	Get values
*/

void			get_op_code(t_car *car, uint8_t op);
int				get_op_data(t_cell *arena, t_car *car);
uint8_t			get_reg_num(t_cell *arena, t_car *car, int arg_num);
int				get_value(t_cell *arena, int start, int size);
int				get_ind(t_cell *arena, t_car *car, int arg_num, int size);

/*
**	Utils
*/

void			skip_op(t_car *car);
int				to_arg(t_car *car, int arg_num);
void			put_on_arena(t_cell *arena, int start, uint8_t *val,
				int s_c[2]);

/*
**	Parser
*/

int				check_flags(int ac, char *av[], int *i);
void			check_flags_priority(void);

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

static void		(*g_opers[17])() = {0, &live_op, &ld_op, &st_op, &add_sub_op,
	&add_sub_op, &and_or_xor_op, &and_or_xor_op, &and_or_xor_op, &zjmp_op,
	&ldi_op, &sti_op, &fork_op, &ld_op, &ldi_op, &fork_op, &aff_op};

/*
**	Visual
*/

void			introduce_champs(t_player *champs);
void			putarena(t_cell *arena);
void			is_winner(void);

void			print_into_arena(t_cell *cells);
void			print_bold(t_cell *cells, int position, int size);
void			print_carrs(t_cell *cells, t_car *carrs);
void			update_view(t_cell *arena);
void			refr(void);
void			disinit(int end);
void			init(void);

/*
**	Tests
*/

void			print_players(t_player *champs);
void			print_cars(t_car *carriage);
void			putfile_hex(int ret, t_cell *file, int space, int newline);
void			putbyte_hex(uint8_t n);
void			putbytes_bit(char *n, int size);
void			print_args_type(t_car *car);

#endif
