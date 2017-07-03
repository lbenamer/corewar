#include "corewar.h"
void disp_pcs(t_pcs *pcs)
{
	t_pcs *tmp;

	tmp = pcs;
	printf("disp pcs : \n");
	while(tmp)
	{
		printf("Process  %d\n", tmp->nb);
		tmp = tmp->prev;
	}
	printf("\n");
}

void disp_vm(t_vm *vm)
{
	t_pl *tmp;
	tmp = vm->plst;
	while(tmp)
	{
		printf(GREEN"Name: %-26s Number: %-4d Alive: %ld (times)\n"STOP, 
			tmp->name, tmp->player, tmp->live);
		tmp = tmp->next;
	}
}

int get_cycles(int rd)
{
	int tab[17] = {0, 10, 5, 5, 10 , 10, 6 , 6, 6,20, 25, 25 ,800, 10 ,50, 1000, 2};
	return(tab[rd]);
}

int	del_pcs(t_pcs *pcs)
{

	printf(RED"Process %d has been destroyed\n"STOP, pcs->nb);
	// free(pcs);
	if(!pcs->next && !pcs->prev)
	{
		pcs = NULL;
		return (-1);
	}
	else if(!pcs->next)
	{		
		pcs = pcs->prev;
		pcs->next = NULL;
	}
	else if(!pcs->prev)
	{
		pcs = pcs->next;
		pcs->prev = NULL;
	}
	else
	{
		pcs = pcs->next;
		pcs->prev = pcs->prev->prev;
		pcs->prev->next = pcs;
		pcs = pcs->prev;
	}
	return (1);
}

int  check_alive(t_pcs *pcs, int *cy, int *die, int *n_check)
{
	int total;
	t_pcs *tmp;

	tmp = pcs;
	total = 0;
	while(tmp)
	{
		if(!tmp->alive)
		{
			if(del_pcs(tmp) == -1)
				return (-1);
			tmp = tmp->prev;
		}
		else
		{
			total += tmp->alive;
			tmp->alive = 0;
			tmp = tmp->prev;	
		}
	}
	if(total >= NBR_LIVE || *n_check == MAX_CHECKS)
		*die -= CYCLE_DELTA;
	*n_check == MAX_CHECKS ? *n_check = 0 : 0;
	if(*die <= 0)
	{
		printf("die is now = %d\n", *die);
		return (-1);
	}
	*cy = 0;
	return (1);
}

void	check_winer(t_vm *vm)
{
	t_pl *pl;

	pl = vm->plst;
	while(pl)
	{
		if(pl->player == vm->last_live)
		{
			printf(GREEN"Player %s [ %d ] Won The Game\n"STOP, pl->name, pl->player);
			break;
		}
		pl = pl->next;
	}
}

void 	run_pcs(t_pcs *pcs, t_vm *vm)
{

	t_pcs *tmp;
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
	tb_instruct[10] = &ldi;
	tb_instruct[11] = &sti;
	tb_instruct[12] = &myfork;
	tb_instruct[13] = &ld;
	tb_instruct[14] = &lldi;
	tb_instruct[0x0F] = &lfork;

	unsigned short rd;
	int cy = 1;
	 // print_mem(vm->ram, MEM_SIZE, 2);
	 printf("\n");
	 // int n;
	 // int i = 0;
	 int n_check = 0;
	 // n = pcs->nb;
	 int die = CYCLE_TO_DIE + CYCLE_DELTA;
	 int total;
	 total = 1;
	 int dump = 2865;

	pcs = place_max(pcs);
	tmp = pcs;
	while(die > 1)
	{
		if (total == dump + 1)
			break;
	
		printf("it's now cycle : %d\n", total);
	 	while(pcs)
	 	{
	 		rd = vm->ram[pcs->pc];
	 		// printf(BLUE"rd = %d pcs->nb = %d\n"STOP, rd, pcs->nb);
	 		if(rd > 0 && rd < 16)
			{	
				// printf("K>O\n");
				if(get_cycles(rd)  == pcs->cycle)
				{
					// printf("K>O 2\n");
					printf("P %d - ", pcs->nb);
					tb_instruct[rd](pcs, vm);
					pcs->cycle = 1;
				}
				else
					++pcs->cycle;
			}
			else
				++pcs->pc;
			pcs = pcs->prev;
	 	}
	 	pcs = tmp;
	 	pcs = place_max(pcs);
	 	++cy;
	 	++total;
	 	// printf("die = %d || cycle = %d \n", die, cy);
	 	if(cy == die)
	 	{
	 		++n_check;
	 		if(check_alive(pcs, &cy, &die, &n_check) == -1)
				break;
	 	}
	}
	printf("it's now cycle : %d\n", total);
	print_mem(vm->ram, MEM_SIZE, 1);
	check_winer(vm);
}