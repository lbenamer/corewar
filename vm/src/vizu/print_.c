#include "../vm/corewar.h"

void print_winner(char *name, int id)
{
	size_t x;
	size_t y;
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

void reverse(int add , unsigned short blink, int color)
{
	size_t x;
	size_t y;
	size_t stx;

	getmaxyx(box_ram, y, x);
	stx = (x - 192) / 2;
	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;
	wattron(box_ram, COLOR_PAIR(color) |  A_REVERSE | A_BOLD);
	mvwprintw(box_ram, y, x, "%.2hhx", blink);
	wattroff(box_ram, A_DIM | COLOR_PAIR(color) | A_REVERSE | A_BOLD) ;
	refresh();
	wrefresh(box_ram);

}



void blink_pos(int add, unsigned short blink, int color)
{
	size_t x;
	size_t y;
	size_t stx;

	getmaxyx(box_ram, y, x);
	stx = (x - 192) / 2;
	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;

	wattron(box_ram, COLOR_PAIR(color) | A_BOLD);
	mvwprintw(box_ram, y, x, "%.2hhx", blink);
	wattroff(box_ram, COLOR_PAIR(color) | A_BOLD) ;
	refresh();
	wrefresh(box_ram);
}

void vizu_print_pgm(t_dt *dt)
{

	int 	add;
	int 	part;
	int 	color;
	t_dt 	*tmp;

	add = 0;
	color = 1;
	tmp = dt;
	part = MEM_SIZE / nb_process(dt);
	i_color(); 
	while(tmp)
	{
		wattron(box_ram, COLOR_PAIR(color));
		vizu_print_mem((unsigned char*)tmp->prog, tmp->size, add);
		wattroff(box_ram, COLOR_PAIR(color));
		add += part;
		++color;
		tmp = tmp->next;
	}

}

void vizu_print_mem(unsigned char *buf, size_t size, size_t add)
{

	size_t x;
	size_t y;
	size_t stx;
	size_t i;

	getmaxyx(box_ram, y, x);
	stx = (x - 192) / 2;

	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;
	i = 0;
	while(i < size)
	{
		mvwprintw(box_ram, y, x, "%.2hhx ", buf[i++]);
		x += 3;
		if(x > stx + 190)
		{
			++y;
			x = stx;
		}
		y %= 64;
	}	
	refresh();
	wrefresh(box_ram);
}

void 	vizu_st(int color, unsigned char *buf, size_t size, size_t add)
{
	wattron(box_ram, COLOR_PAIR(color) | A_BOLD);
	vizu_print_mem(buf, size, add);
	wattroff(box_ram, COLOR_PAIR(color) | A_BOLD);
}










