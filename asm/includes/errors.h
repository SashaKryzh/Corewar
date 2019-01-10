/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:56:16 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/10 11:56:17 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# define NO_NAME 0
# define NO_COMMENT 1
# define NO_NAME_AND_NO_COMMENT 2
# define INCORRECT_FIRST_LINE 3

int		err_mesg(int err_code);

#endif