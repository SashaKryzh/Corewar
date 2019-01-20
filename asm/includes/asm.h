/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:30:52 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/19 13:42:36 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdint.h>
# include "errors.h"
# include "op.h"
# include "../../libft/includes/libft.h"

enum						e_token_type { LABEL, INSTRUCTION, REGISTER,
	DIRECT_VALUE, INDIRECT_VALUE, DIRECT_LABEL, INDIRECT_LABEL, SEPARATOR};

typedef struct	s_token
{
	enum e_token_type		type;
	char					*value;
	int						line;
	struct s_token			*next;
}				t_token;

typedef struct	s_label
{
	char					*label_name;
	int						code_pos;
	struct s_label			*next;
}				t_label;

/*
** structure for compiling input and output files information
*/

typedef struct	s_asm
{
	t_token					*tokens;
	t_label					*labels;
	char					*name;
	char					*comment;
	char					*code;
	int						cur_pos;
	int						size;
	int						fd;
}				t_asm;

/*
** work_with_file.c
*/
void			work_with_file(char *filename);

/*
** write_to_file.c
*/
int				write_to_file(t_asm *champ, char **line, int size);
int				write_magic(t_asm *champ);
int				write_size(t_asm *champ);

/*
** get_name_and_comment.c
*/
int				get_name_and_comment(char **code, t_asm *champ, int *i);

/*
** compile.c
*/
void			compile(char **code, char *filename);

/*
** get_size.c
*/
void			get_size(t_asm *champ);

/*
** get_code.c
*/
int				get_code(t_asm *champ);
void			add_to_code(t_asm *champ, char *new_code, int size);

/*
** hex_func.c
*/
int32_t			hex_to_int(char *hex);
char			*int_to_hex(int32_t nbr, int size);

/*
** tokens.c
*/
int				get_tokens(char **code, t_asm *champ);
int				unknown_character(char c);

/*
** token_with_value.c
*/
int				token_with_value(t_asm *champ, t_token *token, char *value,
		int line_idx);

/*
** get_indirect_value.c
*/
int				get_indirect_value(t_token *token, char *value, int line_idx);

/*
** check.c
*/

/*
** function to check that there is only one instruction per line
*/
int				check_rest(char *str, int start);
int				label_exists(char *label, t_asm *champ);

/*
** label_stuff.c
*/
void			add_label(t_asm *champ, t_token *label);
int				get_label_value(t_token **label, t_asm *champ, int size,
								int start);

/*
** add_token.c
*/
int				add_token(char *line, int i, int *j, t_asm *champ);

/*
** delete.c
*/
void			delete_champ(t_asm *champ);

/*
** skip_coment.c
*/
int				skip_coment(char **code, int *i, int *j);

/*
** assembler functions, each in it's own file
*/
int				add(t_asm *champ, t_token **cur);
int				aff(t_asm *champ, t_token **cur);
int				and(t_asm *champ, t_token **cur);
int				ffork(t_asm *champ, t_token **cur);
int				ld(t_asm *champ, t_token **cur);
int				ldi(t_asm *champ, t_token **cur);
int				lfork(t_asm *champ, t_token **cur);
int				live(t_asm *champ, t_token **cur);
int				lld(t_asm *champ, t_token **cur);
int				lldi(t_asm *champ, t_token **cur);
int				or(t_asm *champ, t_token **cur);
int				st(t_asm *champ, t_token **cur);
int				sti(t_asm *champ, t_token **cur);
int				sub(t_asm *champ, t_token **cur);
int				xor(t_asm *champ, t_token **cur);
int				zjmp(t_asm *champ, t_token **cur);

#endif
