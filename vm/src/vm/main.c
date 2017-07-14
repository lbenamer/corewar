#include "corewar.h"

static void		init_t_vm(t_vm *vm)
{
	vm->cycles = 0;
	vm->last_live = 0;
	vm->plst = new_pl(0, NULL, NULL, 1);
	vm->ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE);
}

int 			main(int ac, char **av)
{
	t_dt	*dt;
	t_vm	vm;
	t_pcs	*pcs;
	int		n;
	
	if (ac < 2)
		disp_usage(0, NULL);
	g_av = av;
	nbr_pcs = 0;
	init_ops(&ops);
	init_t_vm(&vm);
	pcs = new_pcs(0, 0, 1, 1);
	if (!(dt = parse_args(ac, av)))
		disp_usage(0, NULL);
	n = load_ram(dt, vm.ram);
	load_pcs_plst(dt, pcs, vm.plst, n);
	if (ops.all & V)
		display_start(dt, vm.plst);
	run_pcs(pcs, &vm);
	ops.dump && !checkops(V) ? print_mem(vm.ram, MEM_SIZE) : 0;
	if (ops.all & V)
		display_finish();
	return 0;
}
