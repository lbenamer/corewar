#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>


# define STOP     	"\033[0m"    // \033[0
# define BOLD      "" // "\033[1m"
# define ITALIC    "" // "\033[3m"
# define UNDERLINE "" // "\033[4m"
# define BLACK   	"" //"\033[30m"
# define RED     "\033[31m"
# define GREEN   	"\033[32m"    //32
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
	struct s_pcs 	*next;
	struct s_pcs 	*prev;
	int 			color;
	int 			*r;
	int 			id;
	int 			cycle;
	int 			alive;
	unsigned short 	pc;
	char 			carry;
}				t_pcs;

typedef struct s_pl
{
	char 			*name;
	char			*com;
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

typedef void (*t_ins)(t_pcs*, t_vm*);

int 		nbr_pcs;
t_option 	ops;
char 		**g_av;

int 	checkops(int option);

/*
** load_param.c
*/
short 	get_short(char *ram, size_t add);
int 	get_int(char *ram, size_t add);
char 	read_opc(char opc,char n);
int 	load_param(t_pcs *pcs, char *ram, char opc, int *p);
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
** tool.c
*/
int find_nbmax(t_pcs *pcs);
t_pcs 	*place_max(t_pcs *pcs);
// int 	n_pcs(t_pcs *pcs);
int 	get_cycles(int rd);
int 	checkops(int option);
int 	is_set(t_dt *dt, int n);
int 	nb_process(t_dt *dt);
void 	i_color(void);
/*
** parse.c
*/
int 	check_options(char *arg);
void 	disp_usage(int error, char *arg);
t_dt 	*parse_args(int ac, char **av);
/*
** man_list.c
*/
int			load_ram(t_dt *dt, char *ram);
void 		load_pcs_plst(t_dt *dt, t_pcs *pcs, t_pl *pl, int n);
t_pcs  		*new_pcs(int player, int pc, int id, int color);
t_dt  		*new_dt(int fd, int player);
t_pl  		*new_pl(int player, char *name, char *com, int id);
/*
** vm.c
*/
t_pcs 		*del_pcs(t_pcs *pcs);
t_pcs 		*check_alive(t_pcs *pcs, int *total);
t_pcs		*check_to_die(t_pcs *pcs, int *die, int *n_check);
void		check_winer(t_vm *vm);

//main.c
void disp_usage(int error, char *arg);
void 	disp_player(t_dt *dt);

//tool_.c
void 	init_ops(t_option *ops);
int 	is_set(t_dt *dt, int n);
int 	is_num(char *str);
unsigned char	*mem_rev(unsigned char *mem, int n);
void print_mem(char *str, size_t n, int fd);

//get.c

char 	*get_string(int fd, size_t size);
int 	get_size(int fd);
char 	*get_prog(int fd, unsigned int size);
t_dt 	*get_dt(t_dt *dt, int fd);

//chk.c 

int 			chk_magic(int fd);

// run_pcs.c
void 	run_pcs(t_pcs *pcs, t_vm *vm);

// debug :
void disp_dt(t_dt *dt);
void disp_vm(t_vm *vm);
void disp_pcs(t_pcs *pcs);

# include "../vizu/vizu.h"
#endif