#include "../src2/corewar.h"
// #include <ncurses.h>
// #include "vizu.h"


void print_ram(WIN *win);

WIN  *create_box(t_win init, int bd)
{	
	WIN *win;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	
	win = newwin(init.height, init.width, init.starty , init.startx);
	wattron(win, COLOR_PAIR(1));
	box(win, bd, bd);
	refresh();
	wrefresh(win);
	wattroff(win, COLOR_PAIR(1));
	return (win);
}

WIN *init_title(void)
{
	WIN 	*win;
	t_win 	title;	

	title.height = LINES / 10;
	title.width = COLS - 6;
	title.startx = 3;
	title.starty =  1;
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
	ram.starty =    LINES / 10 + 1;
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
	vm.starty = LINES / 10 + 1;
	win = create_box(vm, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

void print_title(WIN *win)
{
	int i;
	int x;
	int y; 
	int hd;
	char **header;
	char *line;

	i = 0;
	wattron(win, COLOR_PAIR(1));
	hd = open("/Users/iLak/42/corewar/ncurses/header_m42.txt", O_RDONLY);
	header = (char **)ft_memalloc(sizeof(char *) * 0x10);
	while(get_next_line(hd, &line) > 0)
		header[i++] = ft_strdup(line);
	getmaxyx(win, y, x);
	i = -1;
	while(header[++i])
	 	mvwprintw(win, i ,  x / 2 - (ft_strlen(header[i]) / 2), "%s", header[i]);
	 refresh();
	 wrefresh(win);
	 wattroff(win, COLOR_PAIR(1));
}

void launch_vizu(void)
{
	int 	ch;

	initscr();
	cbreak();
	start_color();
	assume_default_colors(COLOR_WHITE, COLOR_BLACK);

	box_ram = init_ram();
	box_title = init_title();
	box_vm = init_vm();
	
	 // refresh();
	 print_title(box_title);
	 print_ram(box_ram);
	 refresh();	
	 wrefresh(box_title);
	while((ch = getch()) == 0)
	 	;
	 endwin();
}

void print_ram(WIN *win)
{
	int i;
	int j;
	int x;
	int y;

	wattron(win, A_BOLD);
	getmaxyx(win, y, x);
	y = x;
	j = -1;
	while(++j < 64)
	{
		i = -1;
		x = (y - 192) / 2;
		while(++i < 64)
		{
			mvwprintw(win, j, x, "%.2hhx ", 0);
			x += 3;
		}
	}
	refresh();
	wrefresh(win);
	wattroff(win, A_BOLD);
}

int main(int argc, char const *argv[])
{

	int ch;
	launch_vizu();
	return 0;
}