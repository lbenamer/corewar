#include "corewar.h"

static t_pcs  *new_fork(t_pcs *src, int id, int pc)
{
	t_pcs *pcs;


	nbr_pcs += 1;
	int i = 0;
	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 16);
	pcs->carry = src->carry;
	pcs->alive = src->alive;
	pcs->color = src->color;
	pcs->id = id;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->next = NULL;
	pcs->prev = NULL;
	while(i < 16)
	{
		pcs->r[i] = src->r[i];
		i++;
	}
	ops.all & V ? print_npcs(nbr_pcs) : 0;
	return (pcs);
}


void myfork(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("myfork  -") : 0;
	int p;
	t_pcs *new;
	t_pcs *tmp;
	int pc;

	tmp = pcs;

	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram, pcs->pc);
	(ops.text & 1) ? printf(" %d," , p) : 0;
	p = (pc + p % IDX_MOD) & 0x0fff;
	// p %= MEM_SIZE;
	(ops.text & 1) ? printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 2;
	(ops.text & 1) ? printf("\n") : 0;
}

void lfork(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("lfork  -") : 0;
	int p;
	t_pcs *new;
	t_pcs *tmp;
	int pc;

	pc = pcs->pc;
	tmp = pcs;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram, pcs->pc);
	(ops.text & 1) ? printf(" %d," , p) : 0;
	p = (pc + p) & 0x0fff;
	// p %= MEM_SIZE;
	(ops.text & 1) ? printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 2;
	(ops.text & 1) ? printf("\n") : 0;
}
