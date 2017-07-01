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
	unsigned short 	pc;
	char 	carry;
	int 	*r;
	int  	nb;
	int 	cycle;
	char 	*name;
	struct s_pcs *next;
	struct s_pcs *prev;
}				t_pcs;

typedef struct s_pl
{
	char *name;
	int player;
	unsigned long live;
	struct s_pl *next;
}				t_pl;


typedef struct s_vm
{
	char *ram;
	t_pl  *plst;
}				t_vm;		
 
// instruct.c :
void  	zjmp(t_pcs *pcs, t_vm *vm);
void 	live(t_pcs *pcs , t_vm *vm);
void 	sti(t_pcs *pcs, t_vm *vm);
void 	and(t_pcs *pcs, t_vm *vm);
void 	or(t_pcs *pcs, t_vm *vm);
void 	xor(t_pcs *pcs, t_vm *vm);
void 	st(t_pcs *pcs, t_vm *vm);
void 	ld(t_pcs *pcs, t_vm *vm);
void 	add(t_pcs *pcs, t_vm *vm);
void 	sub(t_pcs *pcs, t_vm *vm);
void 	myfork(t_pcs *pcs, t_vm *vm);
void	lfork(t_pcs *pcs, t_vm *vm);

//get.c

t_dt  *new_dt(int fd, int player);
char *get_string(int fd, size_t size);
int get_size(int fd);
char 	*get_prog(int fd, unsigned int size);
t_dt 	*get_dt(t_dt *dt, int fd);

//chk.c 

unsigned char	*mem_rev(unsigned char *mem, int n);
int 	chk_magic(int fd);

// main.c
t_pcs  *new_pcs(int player, char *name, int pc, int nb);
t_pl  	*new_pl(int player, char *name, unsigned long live);

// run_pcs.c
void 	run_pcs(t_pcs *pcs, t_vm *vm);

// debug :
void disp_dt(t_dt *dt);
void 	disp_pcs(t_pcs *pcs);
void print_mem(char *str, size_t n, int fd);
void disp_vm(t_vm *vm);
#endif