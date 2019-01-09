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

enum e_token_type { NAME, COMMENT, MARK, OPP, T_REG, T_DIR, T_IND};

/*
** work_with_file.c
*/
void		work_with_file(char *filename);

/*
** compile.c
*/
void		compile(char **code, char *filename);

/*
** hex_func.c
*/
int32_t			hex_to_int(char *hex);
char			*int_to_hex(int32_t nbr);

typedef struct	s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}				t_token;

/*
** structure for compiling input and output files information
*/

typedef struct	s_asm
{
	t_token				*tokens;
	int					written_bytes;
	int					fd;
}				t_asm;

#endif
