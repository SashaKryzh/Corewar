/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_oper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 07:44:57 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/10 07:45:02 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op g_op[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.is_args_types = 0,
		.args_types = {T_DIR | 0 | 0},
		.t_dir_size = 4,
		.to_wait = 10
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.is_args_types = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
		.to_wait = 5
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.is_args_types = 1,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.t_dir_size = 4,
		.to_wait = 5
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.to_wait = 10
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.to_wait = 10
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
		.to_wait = 6
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
		.to_wait = 6
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
		.to_wait = 6
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.is_args_types = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.to_wait = 20
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.t_dir_size = 2,
		.to_wait = 25
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.t_dir_size = 2,
		.to_wait = 25
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.is_args_types = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.to_wait = 800
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.is_args_types = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
		.to_wait = 10
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.is_args_types = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.t_dir_size = 2,
		.to_wait = 50
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.is_args_types = 0,
		.args_types = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.to_wait = 1000
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.is_args_types = 1,
		.args_types = {T_REG, 0, 0},
		.t_dir_size = 4,
		.to_wait = 2
	}
};
