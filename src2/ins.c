#include "corewar.h"

void	aff(t_pcs *pcs, t_vm *vm)
{

	int p;
	p = vm->ram[pcs->pc + 1];
	pcs->pc += 2;

}

void 	zjmp(t_pcs *pcs, t_vm *vm)
{
 	(ops.text & 1) ? printf("zjmp -") : 0;
	short p;
	p = get_short(vm->ram , pcs->pc + 1);
	if(pcs->carry)
	{
		p %= MEM_SIZE;
		pcs->pc = pcs->pc + p % IDX_MOD;
		pcs->pc &= 0xfff;
		(ops.text & 1) ? printf(" %d OK :)",p) : 0;
	}
	else
	{
		pcs->pc += 3;
		(ops.text & 1) ? printf("%d FAILED :(", p) : 0;
	}
	(ops.text & 1) ? printf("\n") : 0;
}


void	live(t_pcs *pcs , t_vm *vm)
{
	(ops.text & 1) ? printf("live  -") : 0;
	int p;
	t_pl *tmp;

	p = get_int(vm->ram, 1 + pcs->pc);
	(ops.text & 1) ? printf(" %d," , p) : 0;
	tmp = vm->plst;
	pcs->pc += 5;
	while(tmp)
	{
		if(tmp->player == p)
		{
			++tmp->live;
			vm->last_live = p;
		 	(ops.all & L) ? printf("joueur %s : [p %d] IS ALIVE \n", tmp->name, p) : 0;
			break ;
		}
		tmp = tmp->next;
	}
	++pcs->alive;
	(ops.text & 1) ? printf("\n") : 0;
}