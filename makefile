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
CFLAGS  =  -Wall -Werror -Wextra
LIB		=	-L./vm/libft -lft -lncurses
NAME    =   mafia42
SRCS    =	vm/src/vm/main.c \
			vm/src/vm/get.c \
			vm/src/vm/chk.c \
			vm/src/vm/run_pcs.c \
			vm/src/vm/ins_logic.c \
			vm/src/vm/ins_load.c \
			vm/src/vm/ins_store.c \
			vm/src/vm/ins_fork.c \
			vm/src/vm/ins.c \
			vm/src/vm/tool.c \
			vm/src/vm/load_param.c \
			vm/src/vm/parse.c \
			vm/src/vm/vm.c \
			vm/src/vm/tool_.c \
			vm/src/vm/man_list.c \
			vm/src/vizu/create_win.c \
			vm/src/vizu/launch.c \
			vm/src/vizu/print.c  \
			vm/src/vizu/print_.c 

OBJS    =   $(SRCS:.c=.o)

all:        $(NAME)

$(NAME):    $(OBJS)
			Make -C ./vm/libft
			$(CC) -o $(NAME) $(OBJS) $(LIB)

clean:
			$(RM) $(OBJS)
			Make -C ./vm/libft fclean

fclean:     clean
			$(RM) $(NAME)

re:         fclean all

push:
			@git add .
			@echo "Enter Your Commit :"
			@read var1 ; git commit -m "$$var1"
			@git push

.PHONY:     all clean fclean re push
