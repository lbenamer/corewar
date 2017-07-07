#include <ncurses.h>
#include "../src2/corewar.h"
#include "../libft/libft.h"


#include <ncurses.h>

// typedef struct _win_border_struct {
// 	chtype 	ls, rs, ts, bs, 
// 	 	tl, tr, bl, br;
// }WIN_BORDER;

typedef struct s_win{

	int startx;
	int starty;
	int height;
	int width;

}t_win;

// typedef struct s_co
// {
// 	int x;
// 	int y;
// }				t_co;

// void init_win_params(t_win *p_win);
// void print_win_params(t_win *p_win);
// void create_box(t_win *win, bool flag);

// WINDOW cr_win_type(void)
// {
// 	WINDOW *win;

// 	win->height = 0;
// 	win->width = 0;
// 	win->startx = 0;
// 	win->starty = 0;
	
// 	win->border.ls = '|';
// 	win->border.rs = '|';
// 	win->border.ts = '-';
// 	win->border.bs = '-';
// 	win->border.tl = '*';
// 	win->border.tr = '*';
// 	win->border.bl = '*';
// 	win->border.br = '*';


// 	return (win);
// }


// void print_win(WINDOW *win)
// {

// 	mvaddch(win->starty, win->startx, win->border.tl);    						//ajout des coins avc mvaddch
// 	mvaddch(win->starty, win->startx + win->width, win->border.tr);
// 	mvaddch(win->starty + win->height, win->startx, win->border.bl);
// 	mvaddch(win->starty + win->height, win->startx + win->width, win->border.br);

// 	mvhline(win->starty, win->startx + 1, win->border.ts, win->width - 1); 			// tracage lignes horizontal av mvhline 
// 	mvhline(win->starty + win->height, win->startx + 1, win->border.bs, win->width - 1);			

// 	mvvline(win->starty + 1, win->startx, win->border.ls, win->height - 1);			// tracage lignes vertical av mvvline		
// 	mvvline(win->starty + 1, win->startx + win->width, win->border.rs, win->height - 1);

// 	// refresh();
// }

# define COLOR_GREY COLOR_MAGENTA

int main(int argc, char **argv)
{

	WINDOW *box_vm;
	WINDOW *box_ram;
	WINDOW *box_title;
	
	t_win 	vm;
	t_win 	ram;
	t_win title;

	// WINDOW *title;

	int hd;
	char *line;
	char **header;
	
	initscr();
	cbreak();
	start_color();
	
	hd = open("header_m42.txt", O_RDONLY);
	header = ft_memalloc(sizeof(char *) * 0x10);
	int i = 0;
	while(get_next_line(hd, &line) > 0)
		header[i++] = ft_strdup(line);
	init_color(COLOR_GREY, 89, 90, 91);
	assume_default_colors(COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);


	title.height = LINES / 8;
	title.width = COLS - 6;
	title.startx = 3;
	title.starty =  1;

	vm.height =  LINES - (LINES / 8) - 3;
	vm.width = (COLS / 4) - 3;
	vm.startx = COLS - ( (COLS / 4));
	vm.starty = LINES / 8 + 2;
	
	ram.height =  LINES - (LINES / 8) - 3;
	ram.width =  COLS - (COLS / 4)  - 4;
	ram.startx = 3;
	ram.starty = LINES / 8 + 2;

	refresh();
	box_ram = newwin(ram.height, ram.width, ram.starty ,ram.startx);
	box_vm = newwin(vm.height, vm.width, vm.starty, vm.startx);
	box_title = newwin(title.height, title.width, title.starty, title.startx);
	
	attron(COLOR_PAIR(1));
	wattron(box_vm, COLOR_PAIR(1));
	wattron(box_ram, COLOR_PAIR(1));
	wattron(box_title, COLOR_PAIR(1));
	
	box(stdscr, ' ', ' ');
	box(box_vm, 0, 0);
	box(box_ram, 0, 0);
	box(box_title, ' ', ' ');

	attroff(COLOR_PAIR(1));
	wattroff(box_vm, COLOR_PAIR(1));
	wattroff(box_ram, COLOR_PAIR(1));
	
	refresh();
	wrefresh(box_ram);
	wrefresh(box_vm);
	wrefresh(box_title);
	i = -1;
	int x, y;
	getmaxyx(box_title, y, x);
	while(header[++i])
	 	mvwprintw(box_title, i ,  x / 2 - (ft_strlen(header[i]) / 2), "%s", header[i]);
	wrefresh(box_title);
	wattroff(box_title, COLOR_PAIR(1));

	int cycles = 0;
	getmaxyx(box_vm, y , x);
	wattron(box_vm, A_BOLD);
	mvwprintw(box_vm, i ,  4 , "Cycles : %d ", cycles);
	wattroff(box_vm, A_BOLD);
	wrefresh(box_vm);

	int ch;
	while((ch = getch()) == 0)


	 	
	 endwin();
	return 0;
}