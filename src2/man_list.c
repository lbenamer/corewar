#include "corewar.h"

char	*load_process(t_dt *dt)
{
	char *ram;
	size_t n;
	size_t part;
	t_dt *tmp;

	tmp = dt;
	n = 0;
	part = MEM_SIZE / nb_process(dt);
	ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE);
	while(tmp)
	{
		ft_memcpy(ram + n, tmp->prog, tmp->size);
		n += part;
		tmp = tmp->next;
	}
	return (ram);
}

t_pcs  *new_pcs(int player, int pc, int id, int color)
{
	t_pcs *pcs;

	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 17);
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

void cr_pcs_plst(t_dt *dt, t_pcs **pcs, t_pl **pl)
{
	t_pcs *tmp;
	t_pl *tmp_pl;
	// t_pcs *pcs;
	int pc;
	int id;
	int color;
	int n_pcs;

	color = 1;
	id = 1;
	n_pcs = nb_process(dt);
	pc = MEM_SIZE / n_pcs;
	*pcs = new_pcs(dt->player, 0, id, color);
	*pl = new_pl(dt->player, dt->name, id);
	tmp = *pcs;
	tmp_pl = *pl;
	dt = dt->next;
	while(dt)
	{
		tmp_pl->next = new_pl(dt->player, dt->name, ++id);
		tmp->next = new_pcs(dt->player, pc, id, ++color);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp_pl = tmp_pl->next;
		dt = dt->next;
		pc += MEM_SIZE / n_pcs;
		nbr_pcs += 1;
	}
}

t_pl  	*new_pl(int player, char *name, int id)
{
	t_pl *pl;

	pl = (t_pl*)ft_memalloc(sizeof(t_pl));
	pl->player = player;
	pl->name = name;
	pl->live = 0;
	pl->id = id;
	pl->next = NULL;
	return (pl);
}

t_dt  *new_dt(int fd, int player)
{
	t_dt *dt;

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







