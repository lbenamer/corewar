#include "corewar.h"

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