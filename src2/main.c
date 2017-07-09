#include "corewar.h"
t_option ops;

void i_color(void)
{

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);

}


int 	nb_process(t_dt *dt)
{
	int ret;

	ret = 0;
	if(dt)
		while(dt && ++ret)
			dt = dt->next;
	return (ret);
}

void vizu_print_pgm(t_dt *dt)
{

	int 	add;
	int 	part;
	int 	color;
	t_dt 	*tmp;

	add = 0;
	color = 1;
	tmp = dt;
	part = MEM_SIZE / nb_process(dt);
	i_color();
	while(tmp)
	{
		wattron(box_ram, COLOR_PAIR(color));
		vizu_print_mem((unsigned char*)tmp->prog, tmp->size, add);
		wattroff(box_ram, COLOR_PAIR(color));
		add += part;
		++color;
		tmp = tmp->next;
	}

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

void init_ops(t_option *ops)
{
	ops->all = 0;
	ops->text = 0;
	ops->dump = 0;
	ops->n = 0;
}

int main(int ac, char **av)
{
	t_dt 	*dt;
	t_vm 	vm;
	int 	ch;
	
	nbr_pcs = 0;
	init_ops(&ops);
	t_pcs *pcs = ft_memalloc(sizeof(t_pcs));
	vm.plst = ft_memalloc(sizeof(t_pl));
	dt = parse_args(ac, av);
	vm.ram = load_process(dt);
	(ops.all & V) ? vizu_print_pgm(dt) : 0;
 	cr_pcs_plst(dt, &pcs, &vm.plst);
 	ops.all & V ? print_player(vm.plst) : 0;
 	ops.all & V ? print_npcs(nbr_pcs) : 0; 
 	while(getch() == 0)
		;
	mvwprintw(box_vm, 27, 3, "                                                 ");
	refresh();
	run_pcs(pcs, &vm);
	
	ops.dump ? print_mem(vm.ram, MEM_SIZE, 1) : 0;
	print_finish();
	refresh();

	ch = 0;
	while(!ch)
		ch = getch();
		
	endwin();
	return 0;
}
