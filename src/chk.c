#include "corewar.h"

unsigned char	*mem_rev(unsigned char *mem, int n)
{
	char tmp;
	int i;

	i = 0;
	int nb = n;
	while(--n >= nb / 2)
	{
		tmp = mem[i];
		mem[i++] = mem[n];
		mem[n] = tmp;
	}
	return(mem);
}

int 	chk_magic(int fd)
{
	unsigned int 	magic = COREWAR_EXEC_MAGIC;
	unsigned char* 	octet;
	unsigned char 	buf[4];

	read(fd, buf, 4);
	octet = (unsigned char *) & magic;
	octet = mem_rev(octet, 4);
	return ft_memcmp(octet, buf ,4) ? 0 : 1;
}

void disp_dt(t_dt *dt)
{
	int i;
	while(dt)
	{	
		i = -1;
		printf("********\n");
		printf("player = %d\n", dt->player);
		printf("name = %s\n", dt->name);
		printf("com = %s\n", dt->com);
		printf("size = %d\n", dt->size);
		while(++i < dt->size)
			printf("%x | ", dt->prog[i]);
		printf("\n");
		dt = dt->next;
	}
}

void print_mem(char *str, size_t n, int fd)
{
	size_t i;

	i = -1;
	fd = 0;
	while(++i < n)
	{
		if(((i % 64) == 0) && i)
			dprintf(fd, "\n");
		if(i >= 602 && i <= 605)
			dprintf(fd, GREEN"%.2hhx "STOP, str[i]);
		else if( i == 606)
			dprintf(fd, RED"%.2hhx "STOP, str[i]);
		else if(i < 2048 && str[i] != 0)
			dprintf(fd, BLUE"%.2hhx "STOP, str[i]);
		else if(i >= 2048  && i < 4096 && str[i] != 0)
			dprintf(fd, RED"%.2hhx "STOP, str[i]);
		else
			dprintf(fd, "%.2hhx ", str[i]);
	}
	dprintf(fd,"\n");
	dprintf(fd, "\n");
}