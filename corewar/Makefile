# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 16:06:58 by okryzhan          #+#    #+#              #
#    Updated: 2019/01/21 20:31:14 by vlytvyne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FLAGS = -Wall -Wextra -Werror
CC = gcc $(FLAGS)

VPATH = ./operations || ./parser

SRCS = main.c \
check_args_byte.c \
utils.c \
battle.c \
check_cars.c \
get_value.c \
init_oper.c \
live_op.c \
ld_op.c \
st_op.c \
add_sub_op.c \
and_or_xor_op.c \
zjmp_op.c \
ldi_op.c \
sti_op.c \
fork_op.c \
aff_op.c \
init_battle.c \
parse_players.c \
parser.c \
parser_checks.c \
players_id.c \
check_flags.c \
put_funcs.c \
vis.c \
vis_init.c \
vis_disinit.c

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

LIB_DIR = ../libft
LIB_NAME = ft
LIB = -L $(LIB_DIR) -l$(LIB_NAME)
LIB_HEAD = ../libft/includes
LIBFT = $(LIB_DIR)/libft.a

INCL = ../includes

INCLFORPARSER = .

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@$(CC) -lncurses -o $(NAME) $(OBJS) $(LIB) -I $(LIB_HEAD) -I $(INCL) -I $(INCLFORPARSER)

$(OBJS_DIR)/%.o: %.c *.h ../includes/*.h
	@$(CC) -o $@ -c $< -I $(LIB_HEAD) -I $(INCL) -I $(INCLFORPARSER)

$(OBJS_DIR):
	@mkdir objs

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

clean:
	@rm -rf $(OBJS_DIR)

cleanlib:
	@$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	@rm -rf $(NAME)

fcleanlib:
	@$(MAKE) fclean -C $(LIB_DIR)

re: relib fclean all

relib:
	@$(MAKE) re -C $(LIB_DIR)
