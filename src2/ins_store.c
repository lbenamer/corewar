#include "corewar.h"

void vizu_print_mem(unsigned char *buf, size_t size, size_t add)
{

	int x;
	int y;
	int stx;
	size_t i;

	getmaxyx(box_ram, y, x);
	stx = (x - 192) / 2;

	x = (add % 64) * 3 + stx;
	y = add / 64;
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




static char 	*store(char *mem, unsigned char *store, size_t size, size_t add)
{
	size_t i;

	i = -1;
	while(++i < size)
		mem[(add + i) % MEM_SIZE] = store[i];
	return(mem);
}


void st(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("st - ") : 0;
	int p[2] = {0, 0};
	int pc;
	unsigned char *buf;
	char opc;

	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 0x10, 2, &p[1])) % MEM_SIZE;
	p[1] = pc + (p[1] % IDX_MOD);
	p[1] %=  MEM_SIZE;
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, p[1]);
	if(ops.all & V)
		vizu_st(pcs->color, buf, 4, p[1]);
	(ops.text & 1) ? printf("\n") : 0;
}

void	sti(t_pcs *pcs, t_vm *vm)
{
	int p[3] = {0, 0 , 0};
	int pc;
	unsigned char *buf;
	char opc;

	(ops.text & 1) ? printf("sti - ") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 0x40, 1, &p[0])) % MEM_SIZE;	
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 0x10, 2, &p[1])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs ,vm->ram, opc | 0x04, 3, &p[2])) % MEM_SIZE;
	(ops.text & 1) ? printf("\n         | -> store to: %d + %d = %d ", p[1], p[2], p[1] + p[2]) : 0;
	p[1] = pc + ((p[1] + p[2]) % IDX_MOD);
	p[1] %= MEM_SIZE; // change
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, p[1]);
	(ops.all & V) ? vizu_st(pcs->color, buf, 4, p[1]) : 0;
	(ops.text & 1) ? printf("(with pc and mod: %d)",  p[1]) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}




















