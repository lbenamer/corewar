#ifndef VIZU_H
# define VIZU_H
#include <ncurses.h>

typedef struct _win_st WIN;

typedef struct s_win{

	int startx;
	int starty;
	int height;
	int width;

}t_win;

WIN 	*box_vm;
WIN 	*box_ram;
WIN 	*box_title;

void launch_vizu(void);

#endif