#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/18 18:16:40 by lbenamer          #+#    #+#              #
#    Updated: 2016/12/06 05:07:31 by lbenamer         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC      =   gcc
RM      =   rm -f
CFLAGS  =   -Wall -Werror -Wextra -Wpadded
LIB		=	-L ./libft -lft -lncurses
NAME    =   ../corewar
SRCS    =	src/vm/main.c \
			src/vm/get.c \
			src/vm/run_pcs.c \
			src/vm/ins_load.c \
			src/vm/ins_logic.c \
			src/vm/ins_store.c \
			src/vm/ins_fork.c \
			src/vm/ins.c \
			src/vm/tool.c \
			src/vm/load_param.c \
			src/vm/parse.c \
			src/vm/vm.c \
			src/vm/tool_.c \
			src/vm/man_list.c \
			src/vm/display.c \
			src/vizu/create_win.c \
			src/vizu/launch.c \
			src/vizu/print.c  \
			src/vizu/print_.c \
			src/vizu/print_2.c

OBJS    =   $(SRCS:.c=.o)

all:        $(NAME)

$(NAME):    $(OBJS)
			Make -C libft/
			$(CC) -o $(NAME) $(OBJS) $(LIB)

clean:
			$(RM) $(OBJS)
			Make -C ./libft fclean

fclean:     clean
			$(RM) $(NAME)

re:         fclean all

push:
			@git add .
			@echo "Enter Your Commit :"
			@read var1 ; git commit -m "$$var1"
			@git push

.PHONY:     all clean fclean re push
