#include "corewar.h"

int 	get_short(char *ram)
{
	int ret = 0x0000;

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
	printf("type = %d\n", type);
	if(type == REG_CODE)
	{
		reg = ram[0];
	//	printf("reg = %d\n", reg);
		if(reg < 0 || reg > 16)
			return (-1); // kill process del element list affiche message de kill process ::
		*p = pcs->r[reg - 1];
		return (REG_SIZE);
	}
	else if(type == DIR_CODE)
	{
		*p = get_int(ram);
		return(DIR_SIZE);
	}
	else
	{
		*p = get_short(ram);
		//printf("param = %x\n", *p);
		return (IND_SIZE);
	}
}

void 	zjmp(t_pcs *pcs, char *ram)
{
	unsigned short p;
	p = get_short (ram + 1);
	
	printf("zjmp p = %x\n", p);
	pcs->pc += p;
}

void 	and(t_pcs *pcs, char *ram)
{
	int p[3];
	char opc;
	int pc;

	opc = ram[1];
	pc = load_param(pcs, ram + 2, opc, 1, &p[0]);
	pc += load_param(pcs, ram + 2 + pc, opc ,2 , &p[1]);
	p[2] = ram[pc + 2];
	pcs->r[p[2] - 1] = p[0] & p[1];
	pcs->carry = !pcs->r[p[2] - 1] ?  1 : 0;
	pcs->pc += pc + 2 + 1;
	//printf("p1 = %x, p2 = %x, p3 = %x\n", p[0], p[1], pcs->r[p[2] - 1]);
}

void	sti(t_pcs *pcs, char *ram)
{

	int p[3];
	int pc;
	unsigned char *buf;
	char opc;

	pc = 0;
	opc = ram[1];
	pc = load_param(pcs, ram + 2, opc, 1, &p[0]);
	pc += load_param(pcs, ram + 2 + pc, opc | 0x10 ,2 , &p[1]);
	pc += load_param(pcs ,ram + 2 + pc, opc | 0x04 ,3 , &p[2]);
	p[1] += p[2];
	pcs->carry = !p[1] ? 1 : 0;
	buf = (unsigned char *) & p[0];
	buf = mem_rev(buf, 4);
	ft_strcpy(ram + pcs->pc + p[1], (char*)buf);
	pcs->pc += pc + 2;
}


void	live(t_pcs *pcs , char *ram)
{
	int p;
	t_pcs *tmp;

	p = get_int(ram + 1);
	printf("p = %x\n", p);
	tmp = pcs;
	pcs->pc += 5;
	while(tmp)
	{
		printf("r1 = %d\n", tmp->r[0]);
		if(tmp->r[0] == p)
			printf("joueur %s : [p%d] IS ALIVE \n", tmp->name, p);
		tmp = tmp->next;
	}
}

//  void 	sti(t_pcs *pcs, char *ram)
// {


// // }