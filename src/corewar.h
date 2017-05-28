#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>

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
	size_t 	pc;
	char 	carry;
	int 	r[16];
	char	oct;
	char 	*name;
	struct s_pcs *next;
	struct s_pcs *prev;
}				t_pcs;

typedef struct s_vm
{
	size_t 	live[4];

}				t_vm;
//get.c

t_dt  *new_dt(int fd, int player);
char *get_string(int fd, size_t size);
int get_int(int fd);
char 	*get_prog(int fd, unsigned int size);
t_dt 	*get_dt(t_dt *dt, int fd);

//chk.c 

unsigned char	*mem_rev(unsigned char *mem, int n);
int 	chk_magic(int fd);


// debug :
void disp_dt(t_dt *dt);
void print_mem(char *str, size_t n, int fd);
#endif