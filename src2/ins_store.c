#include "corewar.h"

static char 	*store(char *mem, unsigned char *store, size_t size, size_t add)
{

	size_t i;

	i = -1;
	while(++i < size)
		mem[(add + i) % MEM_SIZE] = store[i];
	return(mem);
}


void st(t_pcs *pcs, t_vm *vm)
{
	(ops.text & 1) ? printf("st - ") : 0;
	int p[2] = {0, 0};
	int pc;
	unsigned char *buf;
	char opc;
	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc , 1, &p[0]);
	if(read_opc(opc, 2) == REG_CODE)
	{
		// printf("if\n");
		p[1] = (vm->ram + pcs->pc)[0] - 1;
		(ops.text & 1) ? printf(" r%d," , p[1]) : 0;
		pcs->r[p[1]]= p[0];
		pcs->pc += 1;
	}
	else
	{
		pcs->pc += load_param(pcs, vm->ram, opc, 2, &p[1]);
		p[1] = pc + p[1] % IDX_MOD;
		// p[1] &= 0x0FFF;
		buf = (unsigned char *) & p[0];
		buf = mem_rev(buf, 4);
		store(vm->ram, buf, 4, p[1]);
	}
	(ops.text & 1) ? printf("\n") : 0;
}

void	sti(t_pcs *pcs, t_vm *vm)
{
	int p[3] = {0, 0 , 0};
	int pc;
	unsigned char *buf;
	char opc;

	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);	
	pcs->pc += load_param(pcs, vm->ram, opc | 0x10 ,2 , &p[1]);
	pcs->pc += load_param(pcs ,vm->ram, opc | 0x04 ,3 , &p[2]);
	(ops.text & 1) ? printf("\n         | -> store to: %d + %d = %d ", p[1], p[2], p[1] + p[2]) : 0;
	p[1] = pc + ((p[1] + p[2]) % IDX_MOD);
	
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, p[1]);
	(ops.text & 1) ? printf("(with pc and mod: %d)",  p[1]) : 0;
	(ops.text & 1) ? printf("\n") : 0;
}