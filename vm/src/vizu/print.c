#include "../vm/corewar.h"

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
