/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:17:43 by pzakala           #+#    #+#             */
/*   Updated: 2018/11/06 10:22:18 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include "stdio.h"
# include "fcntl.h"
# include "libft.h"

# define BUFF_SIZE 1

# define MCHECK(x) if (!(x)) return (-1);

int	get_next_line(const int fd, char **line);

#endif
