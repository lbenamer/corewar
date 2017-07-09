#include "corewar.h"

void sub(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("sub -") : 0;
	int p[3] = {0, 0 , 0};
	char opc;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x10, 2, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] - p[1];
	pcs->carry = !(pcs->r[p[2]]) ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[2] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void 	add(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("add  -") : 0;
	int p[3] = {0, 0 , 0};
	char opc;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x10, 2, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] + p[1];
	pcs->carry = !(pcs->r[p[2]]) ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[2] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void 	and(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("and  -") : 0;
	int p[3] = {0, 0 , 0};
	char opc;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 2, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] & p[1];
	pcs->carry = !(pcs->r[p[2]]) ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[2] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void 	or(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("or -") : 0;
	int p[3] = {0, 0 , 0};
	char opc;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 2, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] | p[1];
	pcs->carry = !(pcs->r[p[2]]) ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[2] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void 	xor(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("xor  -") : 0;
	int p[3] = {0, 0 , 0};
	char opc;

	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 1, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, 2, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] ^ p[1];
	pcs->carry = !(pcs->r[p[2]]) ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[2] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}