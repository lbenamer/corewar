# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/18 03:44:40 by aboudjem          #+#    #+#              #
#    Updated: 2017/07/18 03:47:09 by aboudjem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@printf "\033[1;36mCompiling [\033[1;33masm\033[1;36m]: \033[0m"
	@make -C asm_ > /dev/null
	@echo "✅"
	@printf "\033[1;36mCompiling [\033[1;33mvm\033[1;36m]: \033[0m"
	@make -C vm > /dev/null
	@echo "✅"
	@echo "\033[1;32mCompilation Done !\033[0;0m"

clean:
	@make -C asm_ clean > /dev/null
	@make -C vm clean  > /dev/null

fclean: clean
	@make -C asm_ fclean  > /dev/null
	@make -C vm fclean  > /dev/null

re: fclean all

.PHONY: all, clean, fclean, re
