#include "corewar.h"

char 	*store(char *mem, unsigned char *store, size_t size, size_t add)
{

	size_t i;

	i = -1;
	while(++i < size)
		mem[(add + i) % MEM_SIZE] = store[i];
	return(mem);
}

short 	get_short(char *ram)
{
	short ret = 0x0000;

	ret += (0x00 | (unsigned char)ram[1]);
	ret += (0x00 | (unsigned char)ram[0] ) << 8;
	return (ret);
}

int get_int(char *ram)
{
	int ret;

	ret = 0x00000000;
	ret = (ret | (unsigned char)ram[3]);
	ret += ((0x00 |  (unsigned char)ram[2]) << 8);
	ret += (0x00 | (unsigned char)ram[1]) << 16;
	ret += (0x00 | (unsigned char)ram[0] ) << 24;	
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
		reg = ram[0];
		if(reg > 0 && reg < 17)
			*p = pcs->r[reg - 1];
		printf(" r%d ", reg);
		return (REG_CODE);
	}
	else if(type == DIR_CODE)
	{
		*p = get_int(ram);
		printf(" %d,", *p);
		return(DIR_SIZE);
	}
	else
	{
		*p = get_short(ram);
		printf(" %d,", *p);
		return (IND_SIZE);
	}
}

void 	zjmp(t_pcs *pcs, t_vm *vm)
{
 	printf(YELLOW"zjmp is called -"STOP);
	short p;
	p = get_short(vm->ram + pcs->pc + 1);
	if(pcs->carry)
	{
		pcs->pc += p;
		pcs->pc &= 0x0FFF;
		printf("zjmp -> %d OK ", p);
	}
	else
		printf("zjmp NULL");
	printf("\n");
}

void sub(t_pcs *pcs, t_vm *vm)
{

	int p[3] = {0, 0 , 0};
	int pc;
	char opc;

	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	printf("sub is call -");
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[1]);
	p[2] = (vm->ram + pcs->pc + 2)[pc];
	printf(" r%d," , p[2]);
	if(p[2] > 0 && p[2] < 17)
		pcs->r[p[2] - 1] = p[0] - p[1];
	pcs->carry = !(p[0] - p[1]) ?  1 : 0;
	pcs->pc += pc + 3;
}

void 	add(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"add is called - "STOP);
	int p[3] = {0, 0 , 0};
	int pc;
	char opc;

	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[1]);
	p[2] = (vm->ram + pcs->pc + 2)[pc];
	printf(" r%d," , p[2]);
	if(p[2] > 0 && p[2] < 17)
		pcs->r[p[2] - 1] = p[0] + p[1];
	pcs->carry = !(p[0] + p[1]) ?  1 : 0;
	pcs->pc += pc + 3;
	printf("\n");
}

void 	and(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"and is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;
	int pc;

	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	if(p[2] > 0 && p[2] < 17)
		pcs->r[p[2] - 1] = p[0] & p[1];
	pcs->carry = !(p[0] & p[1]) ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	printf("\n");
}

void 	or(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"or is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;
	int pc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	if(p[2] > 0 && p[2] < 17)
		pcs->r[p[2] - 1] = p[0] | p[1];
	pcs->carry = !(p[0] | p[1]) ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	printf("\n");
}

void 	xor(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"xor is called - "STOP);
	int p[3] = {0, 0 , 0};
	char opc;
	int pc;

	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	if(p[2] > 0 && p[2] < 17)
		pcs->r[p[2] - 1] = p[0] ^ p[1];
	pcs->carry = !(p[0] ^ p[1]) ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	printf("\n");
}

void ld(t_pcs *pcs, t_vm *vm)
{
	
	int p[2] = {0, 0};
	int pc;
	char opc;

	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	p[1] = (vm->ram + pcs->pc + 2)[pc];
	if(p[1] > 0 && p[1] <= 16)
		pcs->r[p[1] - 1] = p[0];
	pcs->carry = !p[0] ?  1 : 0;
	pcs->pc += pc + 3;


	printf(YELLOW"ld is called - "STOP);
	printf(" r%d," , p[1]);
	printf("\n");
}


// void ldi(t_pcs *pcs, t_vm *vm)
// {

// 	int p[3] = {0, 0, 0};
// 	int pc;
// 	char opc;

// 	opc = (vm->ram + pcs->pc)[1];
// 	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc | 0x40, 1, &p[0]);
// 	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc | 0x10, 2, &p[1]);
// 	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc | 0x4, 2, &p[1]);
// 	p[0] += p[1];
// 	p[0] %= IDX_MOD;
	
// 	** il faut lire dans la a l adresse contenu dans p[0] 4 octet,
// 	** les BIG ENDIANISER ET LES FOUTRE DANS UN INT;
// 	** La lecture comme l ecritrure doit tourner sur la Ram (check les autre fct qui ne le font ps)
// 	** Check la total circularite en ecriture/lecture sur tte les instruction possibles;
	

// 	if(p[2] > 0 && p[2] < 17)
// 		pcs->r[p[2] - 1] = p[0];
// 	pcs->pc += pc + 2;

// 	printf(YELLOW"ldi is called - "STOP);
// 	printf(" %d," , p[1]);
// 	printf("\n");
// }



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
	p = get_short(vm->ram + 1 + pcs->pc);
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
	p = get_short(vm->ram + 1 + pcs->pc);
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
	// int cal;
	// unsigned char o;
	char opc;
	// printf(" carry: %d,", pcs->carry);
	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc , 1, &p[0]);
	if(read_opc(opc, 2) == REG_CODE)
	{
		// printf("if\n");
		p[1] = (vm->ram + pcs->pc + 2)[pc];
		printf(" r%d," , p[1]);
		if(p[1] < 17 && p[1] > -1)
			pcs->r[p[1] - 1] = p[0];
		pcs->pc += pc + 3;
	}
	else
	{
		// printf("pc = %d\n", pcs->pc);
		pc += load_param(pcs, vm->ram + 2 + pcs->pc + pc, opc,2 , &p[1]);
		p[1] = pcs->pc + p[1] % IDX_MOD;
		p[1] &= 0x0FFF;
		buf = (unsigned char *) & p[0];
		buf = mem_rev(buf, 4);
		store(vm->ram, buf, 4, p[1]);
		pcs->pc += pc + 2;

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

	pc = 0;	
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);	
	pc += load_param(pcs, vm->ram + 2 + pcs->pc + pc, opc | 0x10 ,2 , &p[1]);
	pc += load_param(pcs ,vm->ram + 2 + pcs->pc + pc, opc | 0x04 ,3 , &p[2]);
	p[1] += p[2];
	p[1] = p[1] % IDX_MOD;
	pcs->carry = !p[1] ? 1 : 0;
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, pcs->pc + p[1]);
	printf(" - store to index : %d - ", pcs->pc + p[1]);
	pcs->pc += pc + 2;
	printf("\n");
}


void	live(t_pcs *pcs , t_vm *vm)
{
	printf(YELLOW"live is called ! - "STOP);
	int p;
	t_pl *tmp;

	p = get_int(vm->ram + 1 + pcs->pc);
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