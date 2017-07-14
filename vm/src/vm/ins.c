#include "corewar.h"

void	aff(t_pcs *pcs, t_vm *vm)
{

	int p;

	p = (vm->ram[pcs->pc + 2] - 1) & 0xf;
	p = (pcs->r[p]) % 256;
	ops.all & A && p  > 32 ? ft_printf("aff: %C\n", p) : 0;
	pcs->pc += 3;

}

void	zjmp(t_pcs *pcs, t_vm *vm)
{
 	(ops.text & 1) ? printf("zjmp -") : 0;
	short	p;
	int		pc;

	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram , pcs->pc);
	if (pcs->carry)
	{
		pcs->pc = (pc + p % IDX_MOD) & 0x0fff;
		(ops.text & 1) ? printf(" %d OK :)",p) : 0;
	}
	else
	{
		pcs->pc += 2;
		(ops.text & 1) ? printf("%d FAILED :(", p) : 0;
	}
	(ops.text & 1) ? printf("\n") : 0;
}


void	live(t_pcs *pcs , t_vm *vm)
{
	(ops.text & 1) ? printf("live  -") : 0;
	int		p;
	t_pl	*tmp;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_int(vm->ram, pcs->pc);
	(ops.text & 1) ? printf(" %d" , p) : 0;
	tmp = vm->plst;
	pcs->pc += 4;
	while (tmp)
	{
		if (tmp->player == p)
		{
			++tmp->live;
			vm->last_live = p;
			(ops.all & L) ? printf("joueur %s : [p %d] IS ALIVE \n", tmp->name, p) : 0;
			ops.all & V ? print_alive(tmp->id, tmp->live) : 0;
			break ;
		}
		tmp = tmp->next;
	}
	++pcs->alive;
	(ops.text & 1) ? printf("\n") : 0;
}
