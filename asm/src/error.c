/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:58:58 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/16 16:08:49 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	error(char *mesg, int line)
{
	ft_putstr_fd("Error in line ", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putendl_fd(mesg, 2);
}

static int	another_variants2(int err_code, int line)
{
	if (err_code == NEXT_TOKEN_MUST_BE_REGISTER)
		error(": Next argument for function must be register!", line);
	else if (err_code == SEPARATOR_IS_MISSING)
		error(": Separator is missing!", line);
	else if (err_code == ARGUMENT_IS_MISSING)
		error(": Argument is missing!", line);
	else if (err_code == NEXT_TOKEN_MUST_BE_DIR_OR_REG)
		error(": Next argument for function must be register or direct value!"
			, line);
	return (0);
}

static int	another_variants(int err_code, int line)
{
	if (err_code == LABEL_DOES_NOT_EXIST)
		error(": Label does not exist!", line);
	else if (err_code == DUPLICATE_VALUE)
		error(": Label with name already exist exist!",
				line);
	else if (err_code == BAD_CHARACTER_IN_INDIRECT_VALUE)
		error(": Bad character in indirect value!", line);
	else if (err_code == BAD_CHARACTER_IN_REGISTER)
		error(": Bad character in register!", line);
	else if (err_code == BAD_REGISTER_IDX)
		error(": Register must be between r1 and r99!",
			line);
	else if (err_code == NEXT_TOKEN_MUST_BE_DIRECT)
		error(": Next argument for function must be direct!", line);
	else if (err_code == ONLY_ONE_INSTRUCTION)
		error(": There must be only one instruction per line!", line);
	else if (err_code == INVALID_INSTRUCTION)
		error(": Invalid instruction!", line);
	else if (err_code == NEXT_TOKEN_MUST_BE_DIR_OR_IN)
		error(": Next argument for function must be direct or indirect!",
			line);
	else
		another_variants2(err_code, line);
	return (0);
}

int			err_mesg(int err_code, int line)
{
	if (err_code == NO_NAME)
		error(": No champion name given!", line);
	else if (err_code == NO_COMMENT)
		error(": No comment given!", line);
	else if (err_code == NO_NAME_AND_NO_COMMENT)
		error(": No champion name and no comment given!",
			line);
	else if (err_code == INCORRECT_FIRST_LINE)
		error(": First line must be champion's name or comment!", line);
	else if (err_code == UNKNOWN_CHARACTER)
		error(": Unknown character!", line);
	else if (err_code == TOO_LONG_CHAMPION_NAME)
		ft_putendl_fd("Champion name is too long!", 2);
	else if (err_code == TOO_LONG_COMMENT)
		ft_putendl_fd("Comment is too long", 2);
	else if (err_code == BAD_CHARACTER_IN_LABEL)
		error(": Bad character in label!", line);
	else if (err_code == BAD_LABEL_FORMAT)
		error(": Label is incorrectly formated!", line);
	else if (err_code == BAD_CHARACTER_IN_DIRECT_VALUE)
		error(": Bad character in direct value!", line);
	else
		another_variants(err_code, line);
	return (0);
}
