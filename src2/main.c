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


void 				init_t_vm(t_vm *vm)
{
	vm->cycles = 0;
	vm->last_live = 0;
	vm->plst = NULL;
	vm->ram = NULL;
}

int main(int ac, char **av)
{
	t_dt 	*dt;
	t_vm 	vm;
	int 	ch;
	
	if(ac == 1)
			disp_usage(0, NULL);

	g_av = av;
	//++g_av;
	nbr_pcs = 0;
	init_ops(&ops);
	init_t_vm(&vm);
	t_pcs *pcs = NULL; 		//(t_pcs*)ft_memalloc(sizeof(t_pcs));
	vm.plst =  NULL;  		//(t_pl*)ft_memalloc(sizeof(t_pl));
	if(!(dt = parse_args(ac, av)))
		disp_usage(0, NULL);
	vm.ram = load_process(dt);
	(ops.all & V) ? vizu_print_pgm(dt) : 0;
 	cr_pcs_plst(dt, &pcs, &vm.plst);
 	ops.all & V ? print_player(vm.plst) : 0;
 	ops.all & V ? print_npcs(nbr_pcs) : 0; 
 	while(getch() == 0)
		;
	del_usage();
	run_pcs(pcs, &vm);
	ops.dump && !checkops(V) ? print_mem(vm.ram, MEM_SIZE, 1) : 0;
	print_finish();
	refresh();
	ch = 0;
	while(!ch)
		ch = getch();
		
	endwin();
	return 0;
}
