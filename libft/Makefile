#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 10:11:34 by okryzhan          #+#    #+#              #
#    Updated: 2018/10/23 10:11:36 by okryzhan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

FLAGS = -Wall -Wextra -Werror
CC = gcc $(FLAGS)

VPATH = ./ft_printf

SRCS = ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memccpy.c \
ft_memmove.c \
ft_memchr.c \
ft_memcmp.c \
ft_memalloc.c \
ft_memdel.c \
ft_memrev.c \
ft_strlen.c \
ft_strdup.c \
ft_strndup.c \
ft_strcpy.c \
ft_strncpy.c \
ft_strcat.c \
ft_strncat.c \
ft_strlcat.c \
ft_strchr.c \
ft_strrchr.c \
ft_strstr.c \
ft_strnstr.c \
ft_strcmp.c \
ft_strncmp.c \
ft_strnew.c \
ft_strdel.c \
ft_strclr.c \
ft_striter.c \
ft_striteri.c \
ft_strmap.c \
ft_strmapi.c \
ft_strequ.c \
ft_strnequ.c \
ft_strsub.c \
ft_strjoin.c \
ft_strtrim.c \
ft_strsplit.c \
ft_strrev.c \
ft_atoi.c \
ft_itoa.c \
ft_itoa_base.c \
ft_sqrt.c \
ft_power.c \
ft_abs.c \
ft_swap.c \
ft_nbrlen.c \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_toupper.c \
ft_tolower.c \
ft_match.c \
ft_contains.c \
ft_putchar.c \
ft_putstr.c \
ft_putnstr.c \
ft_putendl.c \
ft_putnbr.c \
ft_putnbr_base.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_print_bits.c \
ft_lstnew.c \
ft_lstdelone.c \
ft_lstdel.c \
ft_lstadd.c \
ft_lstiter.c \
ft_lstmap.c \
ft_isspace.c \
ft_fibonacci.c \
ft_print_params_delim.c \
get_next_line.c \
ft_printf.c \
parser.c \
display_d.c \
display_c.c \
display_s.c \
display_o.c \
display_u.c \
display_x.c \
display_p.c \
display_f.c \
display_b.c \
get_value.c \
dtoa.c \
utils.c

INC_DIR = ./includes
OBJ_DIR = ./objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir objs

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/*.h
	$(CC) -o $@ -c $< -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re