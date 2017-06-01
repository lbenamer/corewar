#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>

# define STOP      	"\033[0m"
# define BOLD       "\033[1m"
# define ITALIC     "\033[3m"
# define UNDERLINE  "\033[4m"
# define BLACK   	"\033[30m"
# define RED     	"\033[31m"
# define GREEN   	"\033[32m"
# define YELLOW  	"\033[33m"
# define BLUE   	"\033[34m"
# define MAGENTA 	"\033[35m"
# define CYAN    	"\033[36m"
# define WHITE   	"\033[37m"

typedef struct 	s_dt
{
	char 	*name;
	char 	*com;
	char 	*prog;
	int 	size;
	int 	player;
	struct s_dt 	*next;
	struct  s_dt 	*prev;
}				t_dt;

typedef struct s_pcs
{
	short 	pc;
	char 	carry;
	int 	r[16];
	char	oct;
	char 	*name;
	struct s_pcs *next;
	struct s_pcs *prev;
}				t_pcs;

typedef struct s_vm
{

}				t_vm;

// instruct.c :
void 	zjmp(t_pcs *pcs, char *ram);
void	live(t_pcs *pcs , char *ram);
void	sti(t_pcs *pcs, char *ram);
void 	and(t_pcs *pcs, char *ram);

//get.c

t_dt  *new_dt(int fd, int player);
char *get_string(int fd, size_t size);
int get_size(int fd);
char 	*get_prog(int fd, unsigned int size);
t_dt 	*get_dt(t_dt *dt, int fd);

//chk.c 

unsigned char	*mem_rev(unsigned char *mem, int n);
int 	chk_magic(int fd);


// debug :
void disp_dt(t_dt *dt);
void print_mem(char *str, size_t n, int fd);
#endif