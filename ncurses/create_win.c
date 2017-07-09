#include "../src2/corewar.h"
// #include <ncurses.h>
// #include "vizu.h"


void print_ram(WIN *win);

void blink_pos(int add, unsigned short blink, int color)
{
	int x;
	int y;
	int stx;

	getmaxyx(box_ram, y, x);

	stx = (x - 192) / 2;

	x = (add % 64) * 3 + stx;
	y = add / 64;

	 // wattron(box_ram, A_BOLD);
	
	wattron(box_ram, COLOR_PAIR(color) | A_BOLD | A_REVERSE);
	mvwprintw(box_ram, y, x, "%.2hhx", blink);
	wattroff(box_ram, A_DIM | COLOR_PAIR(color)|  A_BOLD | A_REVERSE) ;
	refresh();
	wrefresh(box_ram);

}


void print_winner(char *name, int id)
{

	int x;
	int y;

	getmaxyx(box_vm, y,x);

	wattron(box_vm, A_BOLD);

	mvwprintw(box_vm, 40, (x - 11) / 2, "** PLAYER **");

	wattron(box_vm, COLOR_PAIR(id));
	mvwprintw(box_vm, 42, (x - ft_strlen(name)) / 2, "%s", name);
	wattroff(box_vm, COLOR_PAIR(id));
	mvwprintw(box_vm, 44, (x - 20) / 2,  "!!! WON THE GAME !!!");
	wattroff(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);

}


void print_alive(int id, int live)
{
	int y;
	id == 1 ? y = 12 : 0;
	id == 2 ? y = 16 : 0;
	id == 3 ? y = 20 : 0;	
	id == 4 ? y = 24 : 0;

	wattron(box_vm, A_BOLD);
	wattron(box_vm, COLOR_PAIR(id));
	mvwprintw(box_vm, y, 19, "%d", live);
	wattroff(box_vm, COLOR_PAIR(id));
	wattroff(box_vm, A_BOLD);

	refresh();
	wrefresh(box_vm);
}

void print_npcs(int npcs)
{
	wattron(box_vm, A_BOLD);
	mvwprintw(box_vm, 7, 17, "%4d", npcs);
	wattroff(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);

}

void print_die(int die)
{
	wattron(box_vm, A_BOLD);
	mvwprintw(box_vm, 30, 20, "%4d", die);
	wattroff(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);

}

void print_cycles(int cycle)
{

	wattron(box_vm, A_BOLD);
	mvwprintw(box_vm, 5, 14, "%d", cycle);
	wattroff(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);
}


void print_player(t_pl *pl)
{
	int y;
	int color;

	t_pl *tmp;

	tmp = pl;
	y = 10;
	color = 1;
	wattron(box_vm, A_BOLD);
	while(tmp)
	{	
		mvwprintw(box_vm, y, 5, "Player :");
		wattron(box_vm, COLOR_PAIR(color));
		mvwprintw(box_vm, y, 14, "%s", tmp->name);
		wattroff(box_vm, COLOR_PAIR(color));
		mvwprintw(box_vm, y + 1, 10, "Number : %d", tmp->player);
		mvwprintw(box_vm, y + 2, 10, "lives  : 0");
		
		++color;
		y += 4;
		tmp = tmp->next;
	}
	wattron(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);
}

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
	hd = open("header_m42.txt", O_RDONLY);
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

void print_finish()
{
	char *s;
	int x;
	int y;
	getmaxyx(box_vm, y, x);
	s = "** PRESS ANY KEY TO FINISH **";
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	wattron(box_vm, A_BOLD);
	wattron(box_vm, COLOR_PAIR(5));
	mvwprintw(box_vm, 27, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(box_vm, COLOR_PAIR(5));
	wattroff(box_vm, A_BOLD);
	refresh();
	wrefresh(box_vm);
}

void print_vm(WIN *win)
{

	int x;
	int y;
	getmaxyx(win, y, x);
	wattron(win, A_BOLD);

	char *s;

	s = "** VIRTUAL MACHINE **";
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 2, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(win, COLOR_PAIR(1));
	mvwprintw(win, 5, 5, "Cycles : 0");
	mvwprintw(win, 7, 5, "Processes : ");

	s = "** PRESS ANY KEY TO START **";
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 27, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(win, COLOR_PAIR(1));
	mvwprintw(win, 30, 5, "CYCLE_TO_DIE : %4d", CYCLE_TO_DIE);
	mvwprintw(win, 32, 5, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(win, 34, 5, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(win, 36, 5, "MAX_CHECKS : %d", MAX_CHECKS);
	
	wattroff(win, A_BOLD);
	refresh();
	wrefresh(win);
}

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
	wrefresh(box_title);

}

void print_ram(WIN *win)
{
	int i;
	int j;
	int x;
	int y;

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
}