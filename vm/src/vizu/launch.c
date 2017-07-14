#include "../vm/corewar.h"

void launch_vizu(void)
{
	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
	assume_default_colors(COLOR_WHITE, COLOR_BLACK);

	box_ram = init_ram();
	box_title = init_title();
	box_vm = init_vm();
	
	print_title(box_title);
	print_ram(box_ram);
	print_vm(box_vm);
	refresh();	
}

WIN *init_title(void)
{
	WIN 	*win;
	t_win 	title;	

	title.height = LINES / 10;
	title.width = COLS - 6;
	title.startx = 3;
	title.starty =  0;
	win = create_box(title, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

WIN *init_ram(void)
{
	WIN 	*win;
	t_win 	ram;

	ram.height =   LINES - (LINES / 10) - 1;
	ram.width =  COLS - (COLS / 4)  - 4;
	ram.startx = 3;
	ram.starty =    LINES / 10 ;
	win = create_box(ram, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

WIN *init_vm(void)
{
	WIN 	*win;
	t_win 	vm;

	vm.height =  LINES - (LINES / 10) - 1;
	vm.width = (COLS / 4) - 3;
	vm.startx = COLS - ( (COLS / 4));
	vm.starty = LINES / 10;
	win = create_box(vm, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

void del_usage(void)
{
	mvwprintw(box_vm, 27, 3, "                                                                    ");
	refresh();
	wrefresh(box_vm);	
}
