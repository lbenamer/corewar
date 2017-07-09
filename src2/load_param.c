#include "corewar.h"


short 	get_short(char *ram, size_t add)
{
	short ret = 0x0000;

	add &= 0x0fff;
	ret += (0x00 | (unsigned char)ram[(add + 1) & 0x0fff]);
	ret += (0x00 | (unsigned char)ram[add & 0x0fff] ) << 8;
	return (ret);
}

int get_int(char *ram, size_t add)
{
	int ret;

	ret = 0x00000000;
	add &= 0x0fff;
	ret = (ret | (unsigned char)ram[(add + 3) & 0x0fff]);
	ret += ((0x00 |  (unsigned char)ram[(add + 2) & 0x0fff]) << 8);
	ret += (0x00 | (unsigned char)ram[(add + 1) & 0x0fff]) << 16;
	ret += (0x00 | (unsigned char)ram[add & 0x0fff]) << 24;	
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
		reg = (reg - 1) & 0xf;
		(ops.text & 1) ? printf(" r%d,", reg + 1) : 0;
		*p = pcs->r[reg];
		return (REG_CODE);
	}
	else if(type == DIR_CODE)
	{
		*p = get_int(ram, pcs->pc);
		(ops.text & 1) ? printf(" %d,", *p) : 0;
		return(DIR_SIZE);
	}
	else
	{
		*p = get_short(ram, pcs->pc);
		(ops.text & 1) ? printf(" %d,", *p) : 0;
		return (IND_SIZE);
	}
}