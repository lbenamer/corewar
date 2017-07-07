#include "corewar.h"


void lld(t_pcs *pcs, t_vm *vm)
{
	
	int p[2] = {0, 0};
	char opc;
	int pc;

	(ops.text & 1) ? printf("lld  -") : 0;
	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	if(read_opc(opc, 1) == IND_CODE)
	{
		p[0] += pc;
		p[0] &= 0xFFF;
		p[0] = get_int(vm->ram, p[0] + pc);
	}
	p[1] = (vm->ram + pcs->pc)[0] - 1;
	p[1] &= 0xf;
	pcs->r[p[1]] = p[0];
	pcs->carry = !p[0] ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[1]) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void ld(t_pcs *pcs, t_vm *vm)
{
	
	
	int p[2] = {0, 0};
	char opc;
	int pc;

	(ops.text & 1) ? printf("ld  -") : 0;
	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	if(read_opc(opc, 1) == IND_CODE)
	{
		p[0] %= IDX_MOD;
		p[0] = get_int(vm->ram, p[0] + pc);
	}
	p[1] = (vm->ram + pcs->pc)[0] - 1;
	p[1] &= 0xf;
	pcs->r[p[1]] = p[0];
	pcs->carry = !p[0] ?  1 : 0;
	pcs->pc += 1;

	(ops.text & 1) ? printf(" r%d," , p[1] + 1) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}


void lldi(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("lldi  -") : 0;
	int p[3] = {0, 0, 0};
	char opc;
	int pc;

	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc | 0x40, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x10, 2, &p[1]);
	p[2] = (vm->ram + pcs->pc)[0] - 1;
	p[0] += p[1] + pc;
	p[0] &= 0xfff;
	(ops.text & 1) ? printf("with pc and mod %d," , p[0]) : 0;
	p[0] =  get_int(vm->ram, p[0]);
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0];
	pcs->pc += 1;
	pcs->carry = !p[0] ?  1 : 0;
	(ops.text & 1) ? printf("\n") : 0;
}

void ldi(t_pcs *pcs, t_vm *vm)
{

	(ops.text & 1) ? printf("ldi  -") : 0;
	int p[3] = {0, 0, 0};
	char opc;
	int pc;

	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc | 0x40, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x10, 2, &p[1]);
	p[2] = (vm->ram + pcs->pc)[0] - 1;
	p[0] += p[1];
	p[0] = pc + p[0] % IDX_MOD;
	(ops.text & 1) ? printf("with pc and mod %d," , p[0]) : 0;
	p[0] =  get_int(vm->ram, p[0]);
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0];
	pcs->pc += 1;
	(ops.text & 1) ? printf("\n") : 0;
}