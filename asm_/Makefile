#Library output
NAME = ../asm

#	GCC flags
CFLAGS =  -Wall -Wextra -Werror -g
#	Includes directories
INC_TR = includes
INCLUDES += $(addprefix -iquote , $(INC_TR))

#	Sources
ASM_SOURCES = $(shell find srcs | grep "\.c$$" | sed "s/\.c$$//g")
ASM_HEADERS = $(shell find includes | grep "\.h$$")
SRCS = $(addsuffix .c, $(ASM_SOURCES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME)

# To obtain object files
%.o: %.c $(ASM_HEADERS)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

# To remove generated files
clean:
	@echo "RM\ttous les objects (.o)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "RM\tprojet ($(NAME))"
	@$(RM) $(NAME)

re: fclean all

git:
	@git add .
	@echo "Enter Your Commit :"
	@read var1 ; git commit -m "$$var1"
	@git push
