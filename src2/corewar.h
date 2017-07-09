#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>
# include "../ncurses/vizu.h"

# define STOP     	"\033[0m"    // \033[0
# define BOLD      "" // "\033[1m"
# define ITALIC    "" // "\033[3m"
# define UNDERLINE "" // "\033[4m"
# define BLACK   	"" //"\033[30m"
# define RED     "\033[31m"
# define GREEN   	"\033[32m"
# define YELLOW     "\033[33m"
# define BLUE   	"" //"\033[34m"
# define MAGENTA 	"" //"\033[35m"
# define CYAN    	"\033[36m"
# define WHITE   	"\033[37m"
# define D 1
# define L 2
# define N 4
# define T 8
# define V 16



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
	char 			carry;
	int 			*r;
	int 			id;
	int 			cycle;
	int 			alive;
	int 			color;
	struct s_pcs 	*next;
	struct s_pcs 	*prev;
}				t_pcs;

typedef struct s_pl
{
	char 			*name;
	int 			player;
	unsigned long 	live;
	int 			id;
	struct s_pl 	*next;
}				t_pl;


typedef struct s_vm
{
	char 	*ram;
	t_pl  	*plst;
	int 	last_live;
	int 	cycles;
}				t_vm;		
 
typedef struct s_option
{

	int all;
	int text;
	int dump;
	int n;
}				t_option;

int nbr_pcs;
extern t_option ops;


int 	checkops(int option);

/*
** load_param.c
*/
short 	get_short(char *ram, size_t add);
int 	get_int(char *ram, size_t add);
char 	read_opc(char opc,char n);
int 	load_param(t_pcs *pcs, char *ram, char opc, char n, int *p);
/*
** ins_logic.c
*/
void 	and(t_pcs *pcs, t_vm *vm);
void 	or(t_pcs *pcs, t_vm *vm);
void 	xor(t_pcs *pcs, t_vm *vm);
void 	add(t_pcs *pcs, t_vm *vm);
void 	sub(t_pcs *pcs, t_vm *vm);
/*
** ins_store.c
*/
void 	st(t_pcs *pcs, t_vm *vm);
void 	sti(t_pcs *pcs, t_vm *vm);

/*
** ins_load.c
*/
void 	ldi(t_pcs *pcs, t_vm *vm);
void 	lldi(t_pcs *pcs, t_vm *vm);
void 	lld(t_pcs *pcs, t_vm *vm);
void 	ld(t_pcs *pcs, t_vm *vm);
/*
** ins_fork.c
*/
void 	myfork(t_pcs *pcs, t_vm *vm);
void	lfork(t_pcs *pcs, t_vm *vm);
/*
** ins.c
*/
void  	zjmp(t_pcs *pcs, t_vm *vm);
void 	live(t_pcs *pcs , t_vm *vm);
void 	aff(t_pcs *pcs, t_vm *vm);
/*
**tool.c
*/
int find_nbmax(t_pcs *pcs);
t_pcs *place_max(t_pcs *pcs);
int 	n_pcs(t_pcs *pcs);
int 	get_cycles(int rd);
int 	checkops(int option);
int is_set(t_dt *dt, int n);
/*
**parse.c
*/
int 	check_options(char *arg);
void 	disp_usage(int error, char *arg);
t_dt 	*parse_args(int ac, char **av);

//vizu.c
void vizu_print_mem(unsigned char *buf, size_t size, size_t add);
void print_cycles(int cycle);
void print_player(t_pl *pl);
void print_npcs(int npcs);
void print_alive(int id, int live);
void print_die(int die);
void print_finish(void);
void print_winner(char *name, int id);
void blink_pos(int add, unsigned short blink, int color);

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
t_pcs  *new_pcs(int player, int pc, int nb, int color);
t_pl  	*new_pl(int player, char *name, int id);

// run_pcs.c
void 	run_pcs(t_pcs *pcs, t_vm *vm);

// debug :
void disp_dt(t_dt *dt);
void print_mem(char *str, size_t n, int fd);
void disp_vm(t_vm *vm);
void disp_pcs(t_pcs *pcs);


typedef void (*t_ins)(t_pcs*, t_vm*);
#endif