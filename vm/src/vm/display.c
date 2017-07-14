#include "corewar.h"

static	void	disp_error(int error, char *arg)
{
	ft_printf(RED);
	if (error == -1)
		ft_printf("Error: illegal option: %s\n", arg);
	if (error == -2)
		ft_printf("Error: illegal player id: %s\n", arg);
	if (error == -3)
		ft_printf("Error: illegal dump number: %s\n", arg);
	if (error == -4)
		ft_printf("Error: illegal Text mode: %s\n", arg);
	if (error == -5)
		ft_printf("Error: file %s has a code size that differ from what its header says\n", arg);
	if (error == -6)
		ft_printf("Error: file %s has an invalid header\n", arg);
	if (error == -8)
		ft_printf("Error: too many champions (max 4) : %s\n", arg);
	ft_printf(STOP);
}

void			disp_usage(int error, char *arg)
{
	disp_error(error, arg);
	ft_printf("usage : ./corewar [ -d N | -l | -t N | -v ] | [ -n N ] </path/champ.cor> <...>\n");
	ft_printf(" -a : Prints output from instruction \"aff\"\n");
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

void			disp_player(t_dt *dt)
{
	while (dt)
	{
		printf("Player: [ %d ] - Size : %d oct - Name: %s -> %s \n",dt->player, dt->size, dt->name, dt->com);
		dt = dt->next;
	}
}

void			display_start(t_dt *dt, t_pl *pl)
{
	launch_vizu();
	vizu_print_pgm(dt);
	print_player(pl);
	print_npcs(nbr_pcs);
	while (getch() == 0)
		;
	del_usage();
}

void			display_finish(void)
{
	print_finish();
	refresh();
	while (!getch())
		;
	endwin();
}
