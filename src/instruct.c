#include "corewar.h"

void	live(t_pcs *pcs, t_vm *vm, int param)
{
	while(pcs)
	{
		if(pcs->r[0] == param)
		{
			 ++vm->live[param -1];
			 ft_printf("Player : %s [p%d] is alive !", pcs->name, pcs->r[0]);
		}
		pcs = pcs->next;
	}
}