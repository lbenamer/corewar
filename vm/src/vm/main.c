#include "corewar.h"
t_option ops;


void 	disp_player(t_dt *dt)
{
	while(dt)
	{
		printf("Player: [ %d ] - Size : %d oct - Name: %s -> %s \n",dt->player, dt->size, dt->name, dt->com);
		dt = dt->next;
	}
}



void disp_usage(int error, char *arg)
{
	ft_printf(RED);
	if(error == -1)
		ft_printf("Error: illegal option: %s\n", arg);
	if(error == -2)
		ft_printf("Error: illegal player id: %s\n", arg);
	if(error == -3)
		ft_printf("Error: illegal dump number: %s\n", arg);
	if(error == -4)
		ft_printf("Error: illegal Text mode: %s\n", arg);
	if(error == -5)
		ft_printf("Error: file %s has a code size that differ from what its header says\n", arg);
	if(error == -6)
		ft_printf("Error: file %s has an invalid header\n", arg);
	if(error == -8)
		ft_printf("Error: too many champions (max 4) : %s\n", arg);
	ft_printf(STOP);
	ft_printf("usage : ./corewar [ -d N | -l | -t N | -v ] | [ -n N ] </path/champ.cor> <...>\n");
	ft_printf(" -d : Dumps memory after N cycles then exits \n");
	ft_printf(" -l : Show lives \n");
	ft_printf(" -n : Choose player id (N) Manual mode \n");
	ft_printf(" -t : Text mode (N) \n");
	ft_printf("      ---> N : 1 show instruction\n");
	ft_printf("      ---> N : 2 show cycles\n");
	ft_printf("      ---> N : 4 show death\n");
	ft_printf("      ---> N : 8 show cycles_to_die\n");
	ft_printf("      ---> N : 16 show lives (-l)\n");
	ft_printf(" -v : visual mode\n");
	exit(0);
}

// void disp_pcs(t_pcs *pcs)
// {
// 	while(pcs)
// 	{
// 		printf("pcs id = %d , color = %d, r[0] = %d\n", pcs->id, pcs->color, pcs->r[0]);
// 		pcs = pcs->next;
// 	}
// }


void 				init_t_vm(t_vm *vm)
{
	vm->cycles = 0;
	vm->last_live = 0;
	vm->plst = new_pl(0, NULL, NULL, 1);
	vm->ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE);
}

int main(int ac, char **av)
{
	t_dt 	*dt;
	t_vm 	vm;
	t_pcs *pcs;
	int n;

	
	if(ac == 1)
		disp_usage(0, NULL);



	g_av = av;
	nbr_pcs = 0;
	init_ops(&ops);
	init_t_vm(&vm);
	pcs = new_pcs(0, 0, 1, 1);

	if(!(dt = parse_args(ac, av)))
		disp_usage(0, NULL);

	n = load_ram(dt, vm.ram);
	// print_mem(vm.ram, MEM_SIZE, 1);
 	load_pcs_plst(dt, pcs, vm.plst, n);
 	// disp_pcs(pcs);
 	if(ops.all & V)
 	{
 		// exit(0);
 		launch_vizu();
		vizu_print_pgm(dt);
 		print_player(vm.plst);
 		print_npcs(nbr_pcs); 
 		while(getch() == 0)
			;
		del_usage();
		// refresh();
 	}
	run_pcs(pcs, &vm);
	// free(pcs);
	ops.dump && !checkops(V) ? print_mem(vm.ram, MEM_SIZE, 1) : 0;	
	if(ops.all & V)
	{
		print_finish();
		refresh();
		while(!getch())
			; 	
	 	endwin();
	}
	endwin();
	return 0;
}