#include "corewar.h"


void disp_vm(t_vm *vm)
{
	t_pl *tmp;
	tmp = vm->plst;
	while(tmp)
	{
		printf(GREEN"Name: %-26s Number: %-4d Alive: %-15ld times\n"STOP, 
			tmp->name, tmp->player, tmp->live);
		tmp = tmp->next;
	}
}


int get_cycles(int rd)
{
	int tab[17] = {0, 10, 5, 5, 10 , 10, 6 , 6, 6,20, 25, 25 ,800, 10 ,50, 1000, 2};
	return(tab[rd]);
}

t_pl *dump_pl(t_pl *pl)
{
	t_pl *dump;
	t_pl *tmp;

	dump = new_pl(pl->player, pl->name, pl->live);
	tmp = dump;
	pl = pl->next;
	while(pl)
	{
		tmp->next = new_pl(pl->player, pl->name, pl->live);
		tmp = tmp->next;
		pl = pl->next;
	}
	return (dump);
}


void check_alive(t_vm *vm, int *cv)
{

}


void 	run_pcs(t_pcs *pcs, t_vm *vm)
{
	t_pcs *tmp;
	tmp = pcs;
	while(tmp->next)
		tmp = tmp->next;
	 tmp->next = pcs;
	t_pl *check;
	// disp_pcs(pcs);
	void	(*tb_instruct[17])(t_pcs*, t_vm*);
	tb_instruct[0] = NULL;
	tb_instruct[1] = &live;
	tb_instruct[2] = &ld;
	tb_instruct[3] = &st;
	tb_instruct[4] = &add;
	tb_instruct[5] = &sub;
	tb_instruct[6] = &and;
	tb_instruct[7] = &or;
	tb_instruct[8] = &xor;
	tb_instruct[9] = &zjmp;
	tb_instruct[11] = &sti;
	tb_instruct[0x0C] = &myfork;
	tb_instruct[0x0F] = &lfork;

	unsigned short rd;
	unsigned int cy = 0;
	// int pc = 0;
	// char *mem_fix;
	// mem_fix = vm->ram;
	 print_mem(vm->ram, MEM_SIZE, 2);
	 printf("\n");
	 int n;
	 n = pcs->nb;
		while(pcs)
		{
			if(n == pcs->nb)
			{
				++cy;
				if(cy == 30000)
					break;
			}
			// cycle_less(pcs);
			pcs->pc &= 0x0FFF;
			rd = vm->ram[pcs->pc];
			// printf("rd = %d\n", rd);
			// printf("pc-start  = %d\n", pcs->pc);
			// print_mem(vm->ram, MEM_SIZE, 1);
			// vm->ram += pcs->pc;
			// printf(GREEN"pcs before call ->\n");
			// disp_pcs(pcs);
			// printf("end of disp\n"STOP);
			// printf("P %d - ", pcs->nb);
			if(rd > 0 && rd < 17 && rd != 10)
			{
				// pcs->cycles = get_cycle(rd);// printf("cycle = %d\n", pcs->cycle);
				if(get_cycles(rd) == pcs->cycle)
				{
					printf("P %d - ", pcs->nb);
					tb_instruct[rd](pcs, vm);
					pcs->cycle = 0;
					rd == 0x0C ? pcs = pcs->next : 0;
				}
				else
					++pcs->cycle;
			}
			else
			{
				++pcs->pc;
				// printf("\n");
			}
			// printf("instruct ok\n");
			 // print_mem(vm->ram, MEM_SIZE, 1);
			 // printf("name = %s\n", pcs->name);
			// printf("pc = %d\n", pcs->pc);
				 //printf("next name = %s", pcs->next->name);
			// printf(RED"pcs after call->\n");
			// disp_pcs(pcs);
			// printf("end of disp\n"STOP);
			// printf("turn number %d **** \n", i);
			// print_mem(vm->ram, MEM_SIZE, 1);
			// cycle_less(pcs);
			pcs = pcs->next;
		}

		// disp_vm(vm);
	   print_mem(vm->ram, MEM_SIZE, 2);
}