/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 13:30:52 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/09 13:31:27 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdint.h>
# include "errors.h"

enum e_token_type { LABEL, INSTRUCTION, REGISTER, DIRECT_VALUE,
	INDIRECT_VALUE, DIRECT_LABEL, INDIRECT_LABEL};

typedef struct	s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}				t_token;

/*
** structure for compiling input and output files information
*/

typedef struct	s_asm
{
	t_token				*tokens;
	char				*name;
	char				*comment;
	int					written_bytes;
	int					fd;
}				t_asm;

/*
** work_with_file.c
*/
void		work_with_file(char *filename);

/*
** get_name_and_comment.c
*/
int			get_name_and_comment(char **code, t_asm *champ, int *i);

/*
** compile.c
*/
void		compile(char **code, char *filename);

/*
** hex_func.c
*/
int32_t			hex_to_int(char *hex);
char			*int_to_hex(int32_t nbr);

/*
** tokens.c
*/
int				get_tokens(char **code, t_asm *champ);

#endif
