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
	char		*name;
	char		*comment;
	int			weight;
}				t_player;

#endif
