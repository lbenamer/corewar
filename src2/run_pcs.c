#include "corewar.h"
void disp_pcs(t_pcs *pcs)
{
	t_pcs *tmp;

	tmp = pcs;
	printf("disp pcs : \n");
	while(tmp)
	{
		printf("Process  %d\n", tmp->id);
		tmp = tmp->next;
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


int	del_pcs(t_pcs *pcs)
{
	(ops.text & 4) ? printf("Process %d has been destroyed\n", pcs->id) : 0;
	nbr_pcs -= 1;
	free(pcs->r);
	free(pcs);
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
		pcs->prev->next = pcs->next;
		pcs->next->prev = pcs->prev;
		pcs = pcs->prev;
	}
	ops.all & V ? print_npcs(nbr_pcs) : 0;
	return (1);
}

int check_alive(t_pcs **pcs)
{
	int total;

	total = 0;
	while(*pcs)
	{
		if(!(*pcs)->alive)
		{
			if(del_pcs(*pcs) == -1)
			{
				(ops.text & 4) ? printf("all process are dead \n") : 0;
				return (-1);
			}
			if(!(*pcs)->prev)
				break ;
			*pcs = (*pcs)->prev;
		}
		else
		{
			total += (*pcs)->alive;
			(*pcs)->alive = 0;
			if(!(*pcs)->prev)
				break ;
			*pcs = (*pcs)->prev;	
		}
	}
	*pcs = place_max(*pcs);
	return (total);
}


t_pcs  *check_to_die(t_pcs *pcs, int *die, int *n_check)
{
	static int 	cycle_to_die = CYCLE_TO_DIE;
	int 		total;

	if((total = check_alive(&pcs)) == -1)
		return (NULL);
	if(total >= NBR_LIVE)
	{	
		cycle_to_die -= CYCLE_DELTA;
		*die = cycle_to_die;
		ops.all & V ? print_die(*die) : 0;
		*n_check = 0;
	}
	else if(*n_check == MAX_CHECKS)
	{
			cycle_to_die -= CYCLE_DELTA;
			*die = cycle_to_die;
			ops.all & V ? print_die(*die) : 0;
			*n_check = 0;
	}
	else
		*die = cycle_to_die;
	(ops.text & 8) ? printf("die is now = %d\n", *die) : 0;
	if(*die < 0)
		return (NULL);
	return (pcs);
}

void	check_winer(t_vm *vm)
{
	t_pl *pl;

	pl = vm->plst;
	while(pl)
	{
		if(pl->player == vm->last_live)
		{
			ops.all & V ? print_winner(pl->name, pl->id) : 
			printf(GREEN"Player %s [ %d ] Won The Game\n"STOP, pl->name, pl->player);
			break;
		}
		pl = pl->next;
	}
}

void 	clock(t_pcs *pcs, t_vm *vm, t_ins *ins)
{

 	unsigned short lx;
 	while(pcs)
	{
	 	pcs->pc %= MEM_SIZE;
	 	lx =  vm->ram[pcs->pc];
	 	(ops.text & 1) ? printf(RED"P  %5d | pc = %d | lx = %d \n"STOP, pcs->id, pcs->pc, lx) : 0;
	 	if(lx > 0 && lx < 17)
		{	
			if(get_cycles(lx)  == pcs->cycle)
			{
				ops.all & V ? blink_pos(pcs->pc, lx, pcs->color) : 0;
				(ops.text & 1) ? printf("P  %5d | pc = %d | ", pcs->id, pcs->pc) : 0;
				ins[lx](pcs, vm);
				pcs->cycle = 1;
			}
			else
				++pcs->cycle;
		}
		else
		{
			++pcs->pc;
			++pcs->cycle;
		}
		pcs = pcs->prev;
	 }
}

void init_ins(t_ins *ins)
{
	ins[0] = NULL;
	ins[1] = &live;
	ins[2] = &ld;
	ins[3] = &st;
	ins[4] = &add;
	ins[5] = &sub;
	ins[6] = &and;
	ins[7] = &or;
	ins[8] = &xor;
	ins[9] = &zjmp;
	ins[10] = &ldi;
	ins[11] = &sti;
	ins[12] = &myfork;
	ins[13] = &lld;
	ins[14] = &lldi;
	ins[0x0F] = &lfork;
	ins[16] = &aff;
}


void 	run_pcs(t_pcs *pcs, t_vm *vm)
{
	t_pcs *tmp;
	t_ins *tb_ins;
	int n_check;
	int die;
	int ch;
	 
	die = CYCLE_TO_DIE + 1;
	n_check = 0;
	vm->cycles = 0;
	n_check = 0;
	tb_ins = (t_ins*)ft_memalloc(sizeof(t_ins) * 17);
	init_ins(tb_ins);
	pcs = place_max(pcs);
	while(++vm->cycles && --die >= 0)
	{
		ch = 0;
		if(ops.dump && vm->cycles == ops.dump + 1)
				return ;
		(ops.text & 2) ? printf("its now cycle : %d\n", vm->cycles) : 0;
		ops.all & V ? print_cycles(vm->cycles) : 0;
	 	tmp = pcs;
	 	clock(pcs, vm, tb_ins);
	 	ops.all & V ? usleep(500) : 0;
	 	pcs = place_max(tmp);
	 	if(!die && ++n_check)
	 		if(!(pcs = check_to_die(pcs, &die, &n_check)))
				break;
	}
 	check_winer(vm);
}
