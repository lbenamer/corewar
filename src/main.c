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

t_pcs  *new_pcs(int player, char *name)
{
	t_pcs *pcs;

	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r[0] = player;
	pcs->carry = 0;
	pcs->pc = 0;
	pcs->name = name;
	pcs->next = NULL;
	pcs->prev = NULL;
	return (pcs);
}

t_pcs 	*create_pcs(t_dt *dt, t_pcs *pcs)
{
	t_pcs *tmp;

	pcs = new_pcs(dt->player, dt->name);
	tmp = pcs;
	dt = dt->next;
	while(dt)
	{
		tmp->next = new_pcs(dt->player, dt->name);
		tmp = tmp->next;
		dt = dt->next;
	}
	return (pcs);
}

void 	disp_pcs(t_pcs *pcs)
{
	while(pcs)
	{
		printf("r0 = %d\n", pcs->r[0]);
		printf("name = %s\n", pcs->name);
		pcs = pcs->next;
	}
}

int main(int ac, char const **av)
{
	int i;
	int fd;
	t_dt 	*dt;
	char *ram;
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
	ram = load_process(dt);
	pcs = create_pcs(dt, pcs);
	disp_pcs(pcs);
	sti(pcs, ram);
	//printf("pc = %hd\n", pcs->pc);
	and(pcs, ram + pcs->pc);
	//printf("and pc = %hd\n", pcs->pc);
	live(pcs, ram + pcs->pc);
	//printf("pc = %hd\n", pcs->pc);
	zjmp(pcs, ram + pcs->pc);
	printf("jump pc  = %hd\n", pcs->pc);
	live(pcs, ram + pcs->pc);
//m	printf("pc = %hd\n", pcs->pc);
	print_mem(ram, MEM_SIZE, fd);
	//system("open ram.txt");
	
	return 0;
}