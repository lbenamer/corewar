 #include "corewar.h"
int 	nb_process(t_dt *dt)
{
	int ret;

	ret = 0;
	if(dt)
		while(dt && ++ret)
			dt = dt->next;
	return (ret);
}

char	*load_process(t_dt *dt)
{
	char *ram;
	size_t n;
	size_t part;
	t_dt *tmp;

	tmp = dt;
	n = 0;
	part = MEM_SIZE / nb_process(dt);
	ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE + 1);
	while(tmp)
	{
		ft_memcpy(ram + n, tmp->prog, tmp->size);
		n += part;
		tmp = tmp->next;
	}
	return (ram);
}

t_pcs  *new_pcs(int player, char *name, int pc, int nb)
{
	t_pcs *pcs;

	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 17);
	pcs->r[0] = player;
	pcs->player = player;
	pcs->nb = nb;
	pcs->carry = 0;
	pcs->alive = 0;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->name = name;
	pcs->next = NULL;
	pcs->prev = NULL;
	return (pcs);
}

t_pcs 	*create_pcs(t_dt *dt)
{
	t_pcs *tmp;
	t_pcs *pcs;
	int pc;
	int n_pcs;
	int nb;

	nb = 1;
	n_pcs = nb_process(dt);
	pc = MEM_SIZE / n_pcs;
	pcs = new_pcs(dt->player, dt->name, 0, nb);
	tmp = pcs;
	dt = dt->next;
	while(dt)
	{
		tmp->next = new_pcs(dt->player, dt->name, pc, ++nb);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		dt = dt->next;
		pc += MEM_SIZE / n_pcs;
	}
	return (pcs);
}

t_pl  	*new_pl(int player, char *name, unsigned long live)
{
	t_pl *pl;

	pl = (t_pl*)ft_memalloc(sizeof(t_pl));
	pl->player = player;
	pl->name = name;
	pl->live = live;
	pl->next = NULL;
	return (pl);
}

t_pl *get_pl(t_pcs *pcs)
{

	t_pl *pl;
	t_pl *tmp;
	pl = new_pl(pcs->r[0], pcs->name, 0);
	tmp = pl;
	pcs = pcs->next;
	while(pcs)
	{
		tmp->next = new_pl(pcs->r[0], pcs->name, 0);
		tmp = tmp->next;
		pcs = pcs->next;
	}
	return (pl);
}


int main(int ac, char **av)
{
	int i;
	int fd;
	t_dt 	*dt;
	// char *ram;
	t_vm vm;
	t_pcs *pcs;

	i = -1;
	dt = NULL;
	pcs = NULL;
	if(ac > 5 || ac == 1 )
		return(0);
	while(++i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if(chk_magic(fd))
			dt = get_dt(dt, fd);
	}
	fd = open("ram.txt", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	vm.ram = load_process(dt);
	pcs = create_pcs(dt);
	vm.plst = get_pl(pcs);
	disp_vm(&vm);
	print_mem(vm.ram, MEM_SIZE, 1);
	run_pcs(pcs, &vm);
	// disp_pcs(pcs);
	 disp_vm(&vm);
	return 0;
}