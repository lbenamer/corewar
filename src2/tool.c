#include "corewar.h"

t_pcs *place_max(t_pcs *pcs)
{
	while(pcs->next)
		pcs = pcs->next;
	return (pcs);
}

int get_cycles(int rd)
{
	int tab[17] = {0, 10, 5, 5, 10 , 10, 6 , 6, 6,20, 25, 25 ,800, 10 ,50, 1000, 2};
	return(tab[rd]);
}

int 	checkops(int option)
{
	return (option & ops.all);
}