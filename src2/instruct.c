#include "corewar.h"

char 	*store(char *mem, unsigned char *store, size_t size, size_t add)
{

	size_t i;

	i = -1;
	while(++i < size)
		mem[(add + i) % MEM_SIZE] = store[i];
	return(mem);
}

short 	get_short(char *ram, size_t add)
{
	short ret = 0x0000;

	ret += (0x00 | (unsigned char)ram[(add + 1) % MEM_SIZE]);
	ret += (0x00 | (unsigned char)ram[add % MEM_SIZE] ) << 8;
	return (ret);
}

int get_int(char *ram, size_t add)
{
	int ret;

	ret = 0x00000000;
	ret = (ret | (unsigned char)ram[(add + 3) % MEM_SIZE]);
	ret += ((0x00 |  (unsigned char)ram[(add + 2) % MEM_SIZE]) << 8);
	ret += (0x00 | (unsigned char)ram[(add + 1) % MEM_SIZE]) << 16;
	ret += (0x00 | (unsigned char)ram[add % MEM_SIZE]) << 24;	
	return (ret);
}

char read_opc(char opc,char n)
{
	int ret ;
	ret = 0;
	if(n == 1)
	{
		opc & 0x80 ? ret = DIR_CODE : 0;
		opc & 0x40 ? ret = REG_CODE : 0;
		(opc & 0x80) && (opc & 0x40 ) ? ret = IND_CODE : 0;
	}
	if(n == 2)
	{
		opc & 0x10 ? ret = REG_CODE : 0;
		opc & 0x20 ? ret = DIR_CODE : 0;
		(opc & 0x10) && (opc & 0x20) ? ret = IND_CODE : 0;
	}
	if(n == 3)
	{
		opc & 0x04 ? ret = REG_CODE : 0;
		opc & 0x08 ? ret = DIR_CODE : 0;
		(opc & 0x04) && (opc & 0x08) ? ret = IND_CODE : 0;
	}
	return (ret);
}	

int 	load_param(t_pcs *pcs, char *ram, char opc, char n, int *p)
{
	
	char type;
	int reg;

	type = read_opc(opc, n);
	if(type == REG_CODE)
	{
		reg = ram[pcs->pc];
		reg &= 0xf;
			*p = pcs->r[reg - 1];
		printf(" r%d ", reg);
		return (REG_CODE);
	}
	else if(type == DIR_CODE)
	{
		*p = get_int(ram, pcs->pc);
		printf(" %d,", *p);
		return(DIR_SIZE);
	}
	else
	{
		*p = get_short(ram, pcs->pc);
		printf(" %d,", *p);
		return (IND_SIZE);
	}
}

void 	zjmp(t_pcs *pcs, t_vm *vm)
{
 	printf(YELLOW"zjmp is called -"STOP);
	short p;
	p = get_short(vm->ram , pcs->pc + 1);
	if(pcs->carry)
	{
		pcs->pc += p;
		pcs->pc &= 0x0FFF;
		printf("zjmp -> %d OK ", p);
	}
	else
	{
		pcs->pc += 3;
		printf("zjmp NULL");
	}
	printf("\n");
}

void sub(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"sub is call -"STOP);
	int p[3] = {0, 0 , 0};
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc, 2, &p[1]);
	p[2] = (vm->ram + pcs->pc)[0];
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0] - p[1];
	pcs->carry = !(p[0] - p[1]) ?  1 : 0;
	pcs->pc += 1;

	
	printf(" r%d," , p[2]);
	printf("\n");
}

void 	add(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"add is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc, 2, &p[1]);
	p[2] = (unsigned char)(vm->ram + pcs->pc + 2)[0];
	p[2] &= 0xf;
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] + p[1];
	pcs->carry = !(p[0] + p[1]) ?  1 : 0;
	pcs->pc += 1;
	printf("\n");
}

void 	and(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"and is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[0];
	printf(" r%d," , p[2]);
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0] & p[1];
	pcs->carry = !(p[0] & p[1]) ?  1 : 0;
	pcs->pc += 1;
	printf("\n");
}

void 	or(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"or is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[0];
	printf(" r%d," , p[2]);
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0] | p[1];
	pcs->carry = !(p[0] | p[1]) ?  1 : 0;
	pcs->pc += 1;
	printf("\n");
}

void 	xor(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"xor is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[0];
	printf(" r%d," , p[2]);
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0] ^ p[1];
	pcs->carry = !(p[0] ^ p[1]) ?  1 : 0;
	pcs->pc +=  1;
	printf("\n");
}

void ld(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"ld is called - "STOP);
	
	int p[2] = {0, 0};
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc, 1, &p[0]);
	p[1] = (vm->ram + pcs->pc)[0];
	p[1] &= 0xf;
	pcs->r[p[1] - 1] = p[0];
	pcs->carry = !p[0] ?  1 : 0;
	pcs->pc += 1;


	// printf(YELLOW"ld is called - "STOP);
	printf(" r%d," , p[1]);
	printf("\n");
}


void lldi(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"lldi is called - "STOP);
	int p[3] = {0, 0, 0};
	char opc;
	int pc;

	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc | 0x40, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x10, 2, &p[1]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x4, 3, &p[2]);
	p[0] += p[1];
	// p[0] &= 0x0fff;
	p[0] = get_int(vm->ram, p[0]);
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0];

	// printf(YELLOW"lldi is called - "STOP);
	printf("with pc and mod %d," , p[0]);
	printf("\n");
}

void ldi(t_pcs *pcs, t_vm *vm)
{

	printf(YELLOW"ldi is called - "STOP);
	int p[3] = {0, 0, 0};
	char opc;
	int pc;

	pc = pcs->pc;
	opc = (vm->ram + pcs->pc)[1];
	pcs->pc += 2;
	pcs->pc += load_param(pcs, vm->ram, opc | 0x40, 1, &p[0]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x10, 2, &p[1]);
	pcs->pc += load_param(pcs, vm->ram, opc | 0x4, 3, &p[2]);
	p[0] += p[1];
	p[0] = pc + p[0] % IDX_MOD;
	printf("with pc and mod %d," , p[0]);
	p[0] = get_int(vm->ram, p[0]);
	p[2] &= 0xf;
	pcs->r[p[2] - 1] = p[0];

	// printf(YELLOW"lldi is called - "STOP);
	// printf("with pc and mod %d," , p[0]);
	printf("\n");
}



t_pcs  *new_fork(t_pcs *src, int nb, int pc)
{
	t_pcs *pcs;

	int i = 0;
	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 17);
	pcs->carry = src->carry;
	pcs->alive = 0;
	pcs->nb = nb;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->name = (src->name);
	pcs->next = NULL;
	pcs->prev = NULL;
	while(i < 17)
	{
		pcs->r[i] = src->r[i];
		i++;
	}
	return (pcs);
}


t_pcs *place_max(t_pcs *pcs)
{
	while(pcs->next)
		pcs = pcs->next;
	return (pcs);
}


void myfork(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"myfork is called - "STOP);
	int p;
	t_pcs *new;
	t_pcs *tmp;

	tmp = pcs;
	p = get_short(vm->ram, 1 + pcs->pc);
	printf(" %d," , p);
	p = pcs->pc + p % IDX_MOD;
	p &= 0xFFF;

	printf(" with pc and mod : %d ", p);
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->nb + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;

	pcs->pc += 3;
	printf("\n");
}

void lfork(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"lfork is called - "STOP);
	int p;
	t_pcs *new;
	t_pcs *tmp;

	tmp = pcs;
	p = get_short(vm->ram, 1 + pcs->pc);
	printf(" %d," , p);
	p = pcs->pc + p;
	p &= 0xFFF;
	printf(" with pc and mod : %d ", p);
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->nb + 1, p);
	tmp->next = new;
	new->prev = tmp;

	pcs->pc += 3;
	printf("\n");
}

void st(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"st is called - "STOP);
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
		p[1] = (vm->ram + pcs->pc + 2)[pc];
		printf(" r%d," , p[1]);
		p[1] &= 0xf;
		pcs->r[p[1] - 1] = p[0];
		pcs->pc += 1;
	}
	else
	{
		// printf("pc = %d\n", pcs->pc);
		pcs->pc += load_param(pcs, vm->ram, opc, 2, &p[1]);
		p[1] = pc + p[1] % IDX_MOD;
		p[1] &= 0x0FFF;
		buf = (unsigned char *) & p[0];
		buf = mem_rev(buf, 4);
		store(vm->ram, buf, 4, p[1]);
	}
	printf("\n");
}

void	sti(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"sti is called -"STOP);
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
	 // printf(" %d ", p[2]);
	p[1] += p[2];
	printf(" = %d  ", p[1]);
	p[1] = (pc + p[1]) % IDX_MOD;
	p[1] &= 0x0FFF;
	printf(" with mod and pc %d ", p[1]);
	// printf(" p1 = %d ", p[1]);
	// p[1] &= 0x0FFF;
	pcs->carry = !p[1] ? 1 : 0;
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, p[1]);
	printf(" - store to index : %d - ",  p[1]);
	printf("\n");
}


void	live(t_pcs *pcs , t_vm *vm)
{
	printf(YELLOW"live is called ! - "STOP);
	int p;
	t_pl *tmp;

	p = get_int(vm->ram, 1 + pcs->pc);
	printf(" %d," , p);
	tmp = vm->plst;
	pcs->pc += 5;
	while(tmp)
	{
		if(tmp->player == p)
		{
			++tmp->live;
			vm->last_live = p;
		 	// printf(CYAN"joueur %s : [p %d] IS ALIVE \n"STOP, tmp->name, p);
			break ;
		}
		tmp = tmp->next;
	}
	++pcs->alive;
	printf("\n");
}