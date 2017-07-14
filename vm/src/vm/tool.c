#include "corewar.h"

t_pcs		*place_max(t_pcs *pcs)
{
	while(pcs->next)
		pcs = pcs->next;
	return (pcs);
}

void		free_pcs(t_pcs *pcs)
{
	free(pcs->r);
	free(pcs);
}

int			checkops(int option)
{
	return (option & ops.all);
}

void		i_color(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

int			nb_process(t_dt *dt)
{
	int ret;

	ret = 0;
	if(dt)
		while(dt && ++ret)
			dt = dt->next;
	return (ret);
}
