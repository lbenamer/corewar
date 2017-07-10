#include "corewar.h"

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
