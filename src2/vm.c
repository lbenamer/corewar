#include "corewar.h"

void free_pcs(t_pcs *pcs)
{
	free(pcs->r);
	free(pcs);
}


void disp_pcs(t_pcs *pcs)
{
	while(pcs)
	{
		printf("pcs id = %d , color = %d, r[0] = %d\n", pcs->id, pcs->color, pcs->r[0]);
		pcs = pcs->prev;
	}
}

t_pcs	*del_pcs(t_pcs *pcs)
{

	(ops.text & 4) ? printf(RED"Process %d has been destroyed\n"STOP, pcs->id) : 0;
	t_pcs *tmp_next;
	t_pcs *tmp_prev;

	tmp_next = pcs->next;
	tmp_prev = pcs->prev;
	if(pcs->prev)
	{
		free_pcs(pcs);
		pcs = tmp_prev;
		pcs->next = tmp_next;
		if(tmp_next)
			tmp_next->prev = pcs;
	}
	else if(pcs->next)
	{
		free_pcs(pcs);
		pcs = tmp_next;
		pcs->prev = NULL;
	}
	else
	{
		free_pcs(pcs);
		pcs = NULL;
		(ops.text & 4) ? printf("all process are dead \n") : 0;
		return (NULL);
	}
	return (pcs);
}

t_pcs	*check_alive(t_pcs *pcs, int *total)
{
	// printf("check_alive\n");
	// disp_pcs(pcs);
	while(pcs)
	{
		if(!pcs->alive)
		{
			// printf("kill\n");
			if(!(pcs = del_pcs(pcs)))
				return (NULL);
		}
		else if(pcs->prev)
		{
			*total += pcs->alive;
			pcs->alive = 0;
			pcs = pcs->prev;
		}
		else
		{
			*total += pcs->alive;
			// pcs->alive = 0;
			return (pcs);
		}
	}
	return (pcs);
}


t_pcs  *check_to_die(t_pcs *pcs, int *die, int *n_check)
{
	static int 	cycle_to_die = CYCLE_TO_DIE;
	int 		total;

	total = 0;
	if(!(pcs = check_alive(pcs, &total)))
		return (NULL);
	pcs = place_max(pcs);
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
