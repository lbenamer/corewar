#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "vm/libft/libft.h"
int main(void)
{
	int i = 0;
	while(++i < 108)
	{
		dprintf(1, "\033[%.2dmphrase teste !\n", i);
	}
}