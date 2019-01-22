#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 11:10:21 by okryzhan          #+#    #+#              #
#    Updated: 2019/01/22 11:10:21 by okryzhan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ASM_DIR = ./asm
COREWAR_DIR = ./corewar

LIB_DIR = ./libft

all:
	@echo "Compiling LIB"
	@$(MAKE) all -C $(LIB_DIR)
	@echo "Compiling ASM"
	@$(MAKE) all -C $(ASM_DIR)
	@echo "Compiling COREWAR"
	@$(MAKE) all -C $(COREWAR_DIR)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(MAKE) clean -C $(ASM_DIR)
	@$(MAKE) clean -C $(COREWAR_DIR)

fclean:
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(MAKE) fclean -C $(ASM_DIR)
	@$(MAKE) fclean -C $(COREWAR_DIR)

re: fclean all
