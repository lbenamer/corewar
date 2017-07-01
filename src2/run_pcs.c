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

int 	n_pcs(t_pcs *pcs)
{
	// printf("n_pcs ?\n");
	t_pcs *tmp;
	int nb;
	int ret;

	ret = 1;
	tmp = pcs;
	nb = tmp->nb;
	tmp = tmp->next;
	while(tmp->nb != nb && ++ret)
		tmp = tmp->next;
	// printf("No Way !\n");
	return (ret);
}


int get_cycles(int rd)
{
	int tab[17] = {0, 10, 5, 5, 10 , 10, 6 , 6, 6,20, 25, 25 ,800, 10 ,50, 1000, 2};
	return(tab[rd]);
}

// t_pl *dump_pl(t_pl *pl)
// {
// 	t_pl *dump;
// 	t_pl *tmp;

// 	dump = new_pl(pl->player, pl->name, pl->live);
// 	tmp = dump;
// 	pl = pl->next;
// 	while(pl)
// 	{
// 		tmp->next = new_pl(pl->player, pl->name, pl->live);
// 		tmp = tmp->next;
// 		pl = pl->next;
// 	}
// 	return (dump);
// }

void	del_pcs(t_pcs *pcs)
{

		printf(RED"Process %d has been destroyed\n"STOP, pcs->nb);
		int n;

		n = n_pcs(pcs);
		if(n == 1)
		{
			// printf("n = 1\n");
			pcs->next = NULL;
			pcs->prev = NULL;
			pcs = NULL;
		}
		else
		{
			free(pcs);
			pcs = pcs->prev;
			pcs->next = pcs->next->next;
			pcs->next->prev = pcs;
		}
}

int  check_alive(t_pcs *pcs, int *cy, int *die, int *n_check)
{
	int size;
	int i;
	int total;
	int n;
	t_pcs *tmp;

	size  = n_pcs(pcs);
	tmp = pcs;
	i = 0;
	total = 0;

	while(i < size)
	{
		if(!tmp->alive)
		{
			n = n_pcs(tmp);
			del_pcs(tmp);
			if(n == 1)
			{
				tmp = NULL;
				break ;
			}
		}
		else
			total += tmp->alive;
		tmp = tmp->next;
		++i;	
	}
	// printf("tmp name = %s", tmp->name);
	if(!tmp)
		return (-1);
	 // printf("check alive\n");
	if(total >= NBR_LIVE || *n_check == MAX_CHECKS)
		*die -= CYCLE_DELTA;
	*n_check == MAX_CHECKS ? *n_check = 0 : 0;
	if(*die <= 0)
		return (-1);
	// printf("check alive\n");
	size = n_pcs(tmp);
	// printf("size = %d\n", size);
	i = 0;
	while(i++ < size)
	{
		// printf("i");
		tmp->alive = 0;
		tmp = tmp->next;
	}
	// printf("check alive\n");
	*cy = 0;
	return (1);
}

// int 	n_pcs(t_pcs *pcs)
// {
// 	t_pcs *tmp;
// 	int nb;
// 	int ret;

// 	ret = 0;
// 	tmp = pcs;
// 	nb = tmp->nb;
// 	tmp = tmp->next;
// 	while(tmp->nb != nb && ++ret)
// 		tmp = tmp->next;
// 	return (ret);
// }

void 	run_pcs(t_pcs *pcs, t_vm *vm)
{
	t_pcs *tmp;
	tmp = pcs;
	while(tmp->next)
		tmp = tmp->next;
	 tmp->next = pcs;
	 pcs->prev = tmp->next;
	// t_pl *check;
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
	int cy = 1;
	 // print_mem(vm->ram, MEM_SIZE, 2);
	 printf("\n");
	 int n;
	 int i = 0;
	 int n_check = 0;
	 n = pcs->nb;
	 int die = CYCLE_TO_DIE + CYCLE_DELTA;
	 int total;
	 total = 1;
	// int dump = 8501;
	while(1) 
	{
		// while(cy < die)
		// {
		 	// n = pcs->nb;
		// printf("deb 1\n");
			n = n_pcs(pcs);
			// printf("deb 1.1\n");
			pcs = place_max(pcs);
			// printf("deb 1.2\n");
		 	while(pcs)
		 	{
		 		// printf("deb 2\n");
		 		if(i == n)
		 		{
		 			// printf("its  cycle = %d\n", cy);
		 			 ++cy;
		 			 ++total;
		 			 printf("its  cycle = %d\n", total);
		 			 i = 0;

		 			 n = n_pcs(pcs);
		 			 pcs = place_max(pcs);
		 			 // if(total > 1100)
		 			 // printf("pcs->nb = %d\n", pcs->nb);
		 		}
		 		
		 		 //  printf("n = %d\n", n);
		 		 // printf("i = %d\n", i);
		 		if(cy == die)
		 		{
		 			// printf(GREEN"die  ##############\n"STOP);
		 			break ;
		 		}
		 		// if(total == dump)
		 		//  	break;
		 		// pcs->pc &= 0x0FFF;
				rd = vm->ram[pcs->pc];

		 		if(rd > 0 && rd < 14 && rd != 10)
				{
					// if(pcs->nb == 7)
					// {
					// 	printf("pc = %d\n", pcs->pc);
					// 	// printf("rd = %d\n", rd);
					// }
					if(get_cycles(rd)  == pcs->cycle)
					{

						 printf("P %d - ", pcs->nb);
						tb_instruct[rd](pcs, vm);
						pcs->cycle = 1;
						// if(pcs->nb == 7)
						// {
						// 	printf(" registre r[1] = %d\n", pcs->r[1]);
						// }
					 	// rd == 0x0C ? pcs = pcs->next : 0;
						// printf("die : %d\n", die);
					}
					else
						++pcs->cycle;
				}
				else
					++pcs->pc;
				pcs = pcs->prev;
				++i;
				// ++cy;
		 	}
		// }
		  // if(total == dump)
		  // {
		  // 	 print_mem(vm->ram, MEM_SIZE, 2);
		  // 	break ;
		  // }
		if(cy == die)
		{
			++n_check;
			printf("n_check = %d\n", n_check);
			// if(n_check ==1)
			// {
			// 	printf("cy = %d, die = %d , n_check = %d\n", cy, die, n_check);
			//  	break ;
			// }
			  printf(GREEN"check alive called\n"STOP);
			if(check_alive(pcs, &cy, &die, &n_check) == -1)
				break;
			if(!die)
				break ;
			// printf("cy = %d, die = %d , n_check = %d", cy, die, n_check);
			// printf("ok\n");
			if(!pcs)
				break;
		}
	}
}