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
	@printf "\x1b[38;5;160m"
	@echo " ▄████████  ▄██████▄     ▄████████    ▄████████  ▄█     █▄     ▄████████    ▄████████ "
	@echo "███    ███ ███    ███   ███    ███   ███    ███ ███     ███   ███    ███   ███    ███ "
	@printf "\x1b[38;5;166m"
	@echo "███    █▀  ███    ███   ███    ███   ███    █▀  ███     ███   ███    ███   ███    ███ "
	@printf "\x1b[38;5;226m"
	@echo "███        ███    ███  ▄███▄▄▄▄██▀  ▄███▄▄▄     ███     ███   ███    ███  ▄███▄▄▄▄██▀ "
	@printf "\x1b[38;5;28m"
	@echo "███        ███    ███ ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ███     ███ ▀███████████ ▀▀███▀▀▀▀▀   "
	@printf "\x1b[38;5;19m"
	@echo "███    █▄  ███    ███ ▀███████████   ███    █▄  ███     ███   ███    ███ ▀███████████ "
	@printf "\x1b[38;5;126m"
	@echo "███    ███ ███    ███   ███    ███   ███    ███ ███ ▄█▄ ███   ███    ███   ███    ███ "
	@echo "████████▀   ▀██████▀    ███    ███   ██████████  ▀███▀███▀    ███    █▀    ███    ███ "
	@echo "                        ███    ███                                         ███    ███ "
	@printf "\x1b[32;1m"
	@echo "[✓]Compiling LIB"
	@$(MAKE) all -C $(LIB_DIR)
	@echo "[✓]Compiling ASM"
	@$(MAKE) all -C $(ASM_DIR)
	@echo "[✓]Compiling COREWAR"
	@$(MAKE) all -C $(COREWAR_DIR)
	@printf "\x1b[0m"

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(MAKE) clean -C $(ASM_DIR)
	@$(MAKE) clean -C $(COREWAR_DIR)

fclean:
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(MAKE) fclean -C $(ASM_DIR)
	@$(MAKE) fclean -C $(COREWAR_DIR)

re: fclean all
