#include "corewar.h"

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
	// printf("type = %d\n", type);
	if(type == REG_CODE)
	{
		reg = ram[0];
	//	printf("reg = %d\n", reg);
		if(reg < 0 || reg > 16)
			return (-1); // kill process del element list affiche message de kill process ::
		*p = pcs->r[reg - 1];
		printf(" r%d,", reg);
		return (REG_SIZE);
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
		//printf("param = %x\n", *p);
		return (IND_SIZE);
	}
}

void 	zjmp(t_pcs *pcs, t_vm *vm)
{
 	printf(YELLOW"zjmp is called -"STOP);
	short p;
	// printf("zjmp ");
	// printf(" carry: %d,", pcs->carry);
	p = get_short(vm->ram + pcs->pc + 1);
	
	// printf("zjmp p = %x\n", p);
	if(pcs->carry)
	{
		pcs->pc += p;
		pcs->pc &= 0x0FFF;
		printf("zjmp -> %d OK ", p);
	}
	else
		printf("zjmp NULL");
	pcs->cycle = 20;
	printf("\n");
}

void sub(t_pcs *pcs, t_vm *vm)
{

	int p[3];
	int pc;
	char opc;

	// printf(" carry: %d,", pcs->carry);
	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	printf("sub is call -");
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[1]);
	p[2] = (vm->ram + pcs->pc + 2)[pc];
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] - p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 3;
	pcs->cycle = 10;
}

void 	add(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"add is called - "STOP);
	int p[3];
	int pc;
	char opc;

	// printf(" carry: %d,", pcs->carry);
	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[1]);
	p[2] = (vm->ram + pcs->pc + 2)[pc];
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] + p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 3;
	pcs->cycle = 10;
	printf("\n");
}

void 	and(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"and is called - "STOP);
	int p[3];
	char opc;
	int pc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] & p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	//printf("p1 = %x, p2 = %x, p3 = %x\n", p[0], p[1], pcs->r[p[2] - 1]);
	pcs->cycle = 6;
	printf("\n");
}

void 	or(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"or is called - "STOP);
	int p[3];
	char opc;
	int pc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] | p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	pcs->cycle = 6;
	printf("\n");
}

void 	xor(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"xor is called - "STOP);
	int p[3];
	char opc;
	int pc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	pc += load_param(pcs, vm->ram + 2 + pc + pcs->pc, opc ,2 , &p[1]);
	p[2] = (vm->ram + pcs->pc)[pc + 2];
	printf(" r%d," , p[2]);
	pcs->r[p[2] - 1] = p[0] ^ p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	pcs->cycle = 6;
	printf("\n");
}

void ld(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"ld is called - "STOP);
	int p[2];
	int pc;
	char opc;

	// printf(" carry: %d,", pcs->carry);
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);
	p[1] = (vm->ram + pcs->pc + 2)[pc];
	printf(" r%d," , p[1]);
	if(p[1] >= 0 && p[1] <= 16)
		pcs->r[p[1] - 1] = p[0];
	pcs->carry = !p[0] ?  1 : 0;
	pcs->pc += pc + 3;
	pcs->cycle = 5;
	printf("\n");
}


t_pcs  *new_fork(t_pcs *src, int nb, int pc)
{
	t_pcs *pcs;

	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 17);
	pcs->r = src->r;
	pcs->carry = src->carry;
	pcs->nb = nb;
	pcs->pc = pc;
	pcs->cycle = 0;
	pcs->name = src->name;
	pcs->next = NULL;
	pcs->prev = NULL;
	return (pcs);
}

int find_nbmax(t_pcs *pcs)
{
	int max;
	t_pcs *tmp;
	
	max = 0;
	tmp = pcs;
	while(tmp)
	{
		if(max < tmp->nb)
		{
			max = tmp->nb;
			tmp = tmp->next;
		}
		else if(max == tmp->nb)
			break ;
		else
			tmp = tmp->next;
	}
	return (max);
}

void myfork(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"myfork is called - "STOP);
	int p;
	t_pcs *new;
	int nb;

	// printf(" carry: %d,", pcs->carry);
	p = get_short(vm->ram + 1 + pcs->pc);
	printf(" %d," , p);
	p = pcs->pc + p % IDX_MOD;
	printf(" with pc and mod : %d ", p);
	nb = find_nbmax(pcs);
	// printf(" nb = %d, ", nb);
	// p &= 0x0FFF;
	// printf("param = %d\n", p);

	new = new_fork(pcs, ++nb, p);
	new->next = pcs->next;
	pcs->next = new;
	pcs->pc += 3;
 	pcs->cycle = 800;
	 // pcs = pcs->next;
	printf("\n");
}

void lfork(t_pcs *pcs, t_vm *vm)
{
	printf(YELLOW"myfork is called - "STOP);
	int p;
	t_pcs *new;
	int nb;

	// printf(" carry: %d,", pcs->carry);
	p = get_short(vm->ram + 1 + pcs->pc);
	printf(" %d," , p);
	p = pcs->pc + p;
	nb = find_nbmax(pcs);
	// printf(" nb = %d, ", nb);
	// p &= 0x0FFF;
	// printf("param = %d\n", p);

	new = new_fork(pcs, +nb, p);
	new->next = pcs->next;
	pcs->next = new;
	pcs->pc += 3;
	// pcs = pcs->next;
	pcs->cycle = 1000;
	printf("\n");
}

void st(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"st is called - "STOP);
	int p[2];
	int pc;
	unsigned char *buf;
	char opc;
	// printf(" carry: %d,", pcs->carry);
	pc = 0;
	opc = (vm->ram + pcs->pc)[1];
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc | 0x40, 1, &p[0]);
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
		pc += load_param(pcs, vm->ram + 2 + pcs->pc + pc, opc | 0x10 ,2 , &p[1]);
		// printf("param 1 = %d, param 2 = %d \n", p[0], p[1]);
		// printf("param 1 = %d, param 2 %d \n", p[0], p[1]);

		p[1] = pcs->pc + p[1] % IDX_MOD;
		// p[1] &= 0x0FFF;
	 	// printf(RED"param 1 = %d, param 2 %d \n"STOP, p[0], p[1]);
		buf = (unsigned char *) & p[0];
		buf = mem_rev(buf, 4);
		ft_strncpy((vm->ram + p[1]), (char*)buf, 4);
		pcs->pc += pc + 2;

	}
	printf("\n");
	pcs->cycle = 5;
//	pc += load_param(pcs, vm->ram + 2 + pcs->pc + pc, opc | 0x10 ,2 , &p[1]);


}

void	sti(t_pcs *pcs, t_vm *vm)
{
	 printf(YELLOW"sti is called -"STOP);
	int p[3];
	int pc;
	unsigned char *buf;
	char opc;

	pc = 0;	
	opc = (vm->ram + pcs->pc)[1];
	// printf(" cy: %d,", pcs->carry);
	pc = load_param(pcs, vm->ram + 2 + pcs->pc, opc, 1, &p[0]);	// printf("sti p1 = %d\n", p[0]);
	pc += load_param(pcs, vm->ram + 2 + pcs->pc + pc, opc | 0x10 ,2 , &p[1]);
	pc += load_param(pcs ,vm->ram + 2 + pcs->pc + pc, opc | 0x04 ,3 , &p[2]);
	// printf("p1 = %d p2 = %d, p3 = %d \n", p[0], p[1], p[2]);
	p[1] += p[2];
	pcs->carry = !p[1] ? 1 : 0;
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	// print_mem((char*)buf, 4, 1);
	// printf("sti pc = %d\n", pcs->pc);
	ft_strncpy((vm->ram + pcs->pc + p[1]), (char*)buf, 4);
	printf(" - store to index : %d - ", pcs->pc + p[1]);
	pcs->pc += pc + 2;
	pcs->cycle = 25;
	printf("\n");
}


void	live(t_pcs *pcs , t_vm *vm)
{
	 printf(YELLOW"live is called ! - "STOP);
	int p;
	t_pl *tmp;

	p = get_int(vm->ram + 1 + pcs->pc);
	printf(" %d," , p);
	// printf("p live = %x\n", p);
	tmp = vm->plst;
	pcs->pc += 5;
	while(tmp)
	{
		// printf("players = %d\n", tmp->player);
		if(tmp->player == p)
		{
			++tmp->live;
		 	// printf(CYAN"joueur %s : [p %d] IS ALIVE \n"STOP, tmp->name, p);
			break ;
		}
		tmp = tmp->next;
	}
	printf("\n");
	pcs->cycle = 10;
}