# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 14:37:31 by amoroziu          #+#    #+#              #
#    Updated: 2019/01/15 16:10:22 by amoroziu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

# srcs, path and obj

SRC_N			=	add_token.c \
					add.c \
					aff.c \
					and.c \
					fork.c \
					ld.c \
					ldi.c \
					lfork.c \
					live.c \
					lld.c \
					lldi.c \
					or.c \
					st.c \
					sti.c \
					sub.c \
					xor.c \
					zjmp.c \
					check.c \
					compile.c \
					error.c \
					get_code.c \
					get_indirect_value.c \
					get_name_and_comment.c \
					hex_func.c \
					label_stuff.c \
					main.c \
					prepare_labels.c \
					token_with_value.c \
					tokens.c \
					work_with_file.c \
					write_to_file.c

SRC_P 			= ./src/
OBJ 			= $(addprefix $(OBJ_P),$(SRC_N:.c=.o))
OBJ_P			= ./obj/
INC 			= $(addprefix -I, $(INC_P))
INC_P			= ./includes/

# libft

LIB_P			= ../libft/
ADD_LIB			= $(addprefix $(LIB_P), libft.a)
INC_LIB			= -I ../libft
LNK_LIB			= -L ../libft -l ft

# compiler

CC 				= gcc
CC_FLAGS 		= -Wall -Wextra -Werror

all: obj $(ADD_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_P)

$(OBJ_P)%.o:$(SRC_P)%.c ./includes/asm.h ./includes/op.h ./includes/errors.h
	@$(CC) $(CC_FLAGS) $(INC_LIB) -I $(INC_P) -o $@ -c $<

$(ADD_LIB):
	@make -C $(LIB_P)

$(NAME): $(OBJ)
	@$(CC) $(LNK_LIB) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ_P)
	@make -C $(LIB_P) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_P) fclean

re: fclean all

.PHONY: all clean fclean re
