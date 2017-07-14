#ifndef VIZU_H
# define VIZU_H
# include <ncurses.h>


typedef struct	_win_st 	WIN;
typedef struct				s_win
{
	int	startx;
	int	starty;
	int	height;
	int	width;
}							t_win;

 WIN 						*box_vm;
 WIN 						*box_ram;
 WIN 						*box_title;

/*
**launch.c
*/
void 						launch_vizu(void);
WIN							*init_title(void);
WIN							*init_ram(void);
WIN							*init_vm(void);
void						del_usage(void);
/*
**create_win.c
*/
void						print_title(WIN *win);
WIN							*create_box(t_win init, int bd);
void						print_vm(WIN *win);
void						print_ram(WIN *win);
void 						print_player(t_pl *pl);
/*
**print.c
*/
void						print_alive(int id, int live);
void						print_npcs(int npcs);
void						print_die(int die);
void						print_cycles(int cycle);
void						print_finish(void);
/*
**print_.c
*/
void						print_winner(char *name, int id);
void						blink_pos(int add, unsigned short blink, int color);
void						vizu_print_mem(unsigned char *buf, size_t size, size_t add);
void 						vizu_print_pgm(t_dt *dt);
void 						vizu_st(int color, unsigned char *buf, size_t size, size_t add);
void 						reverse(int add , unsigned short blink, int color);
#endif
