#include "corewar.h"

static t_pcs  *new_fork(t_pcs *src, int id, int pc)
{
	t_pcs *pcs;

	int i = 0;
	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 17);
	pcs->carry = src->carry;
	pcs->alive = src->alive;
	pcs->id = id;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->next = NULL;
	pcs->prev = NULL;
	while(i < 17)
	{
		pcs->r[i] = src->r[i];
		i++;
	}
	return (pcs);
}


void myfork(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("myfork  -") : 0;
	int p;
	t_pcs *new;
	t_pcs *tmp;

	tmp = pcs;
	p = get_short(vm->ram, 1 + pcs->pc);
	(ops.text & 1) ? printf(" %d," , p) : 0;
	p = pcs->pc + p % IDX_MOD;
	p &= 0xFFF;
	(ops.text & 1) ? printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 3;
	(ops.text & 1) ? printf("\n") : 0;
}

void lfork(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("lfork  -") : 0;
	int p;
	t_pcs *new;
	t_pcs *tmp;

	tmp = pcs;
	p = get_short(vm->ram, 1 + pcs->pc);
	(ops.text & 1) ? printf(" %d," , p) : 0;
	p = pcs->pc + p;
	p &= 0xFFF;
	(ops.text & 1) ? printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 3;
	(ops.text & 1) ? printf("\n") : 0;
}