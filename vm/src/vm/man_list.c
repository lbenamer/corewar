#include "corewar.h"

int	load_ram(t_dt *dt, char *ram)
{
	size_t n;
	size_t part;
	int 	ret;
	// t_dt 	*tmp;


	n = 0;
	ret = 0;
	part = MEM_SIZE / nb_process(dt);
	// ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE);
	while(dt)
	{
		ft_memcpy(ram + n, dt->prog, dt->size);
		n += part;
		++ret;
		dt = dt->next;
	}
	return (ret);
}

t_pcs  *new_pcs(int player, int pc, int id, int color)
{
	t_pcs *pcs;

	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 16);
	pcs->r[0] = player;
	pcs->color = color;
	pcs->id = id;
	pcs->carry = 0;
	pcs->alive = 0;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->next = NULL;
	pcs->prev = NULL;
	return (pcs);
}

void load_pcs_plst(t_dt *dt, t_pcs *pcs, t_pl *pl, int n)
{
	// t_pcs *tmp;
	// t_pl *tmp_pl;
	int pc;
	int id;
	// int color;

	// color = 1;
	id = 1;
	pc = MEM_SIZE / n;

	pcs->r[0] = dt->player;	
	pl->player = dt->player;
	pl->name = dt->name;
	pl->com = dt->com;
	// pcs = new_pcs(dt->player, 0, id, id);
	// pl = new_pl(dt->player, dt->name, id);
	dt = dt->next;
	while(dt)
	{
		pl->next = new_pl(dt->player, dt->name, dt->com, ++id);
		pcs->next = new_pcs(dt->player, pc, id, id);
		pcs->next->prev = pcs;
		pcs = pcs->next;
		pl = pl->next;
		dt = dt->next;
		pc += MEM_SIZE / n;
		nbr_pcs += 1;
	}
}

t_pl  	*new_pl(int player, char *name, char *com, int id)
{
	t_pl *pl;

	pl = (t_pl*)ft_memalloc(sizeof(t_pl));
	pl->player = player;
	pl->com = com;
	pl->name = name;
	pl->live = 0;
	pl->id = id;
	pl->next = NULL;
	return (pl);
}

t_dt  *new_dt(int fd, int player)
{
	t_dt *dt;
	static int max = 0;

	++max;
	max > 4 ? disp_usage(-8, *g_av) : 0;
	dt = (t_dt*)ft_memalloc(sizeof(t_dt));
	dt->name = get_string(fd, PROG_NAME_LENGTH + 4);
	dt->size = (unsigned int)get_size(fd);
	dt->com = get_string(fd, COMMENT_LENGTH + 4);
	dt->prog = get_prog(fd, dt->size);
	dt->player = player;
	dt->next = NULL;
	dt->prev = NULL;
	return (dt); 
}
