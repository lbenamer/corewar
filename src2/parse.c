#include "corewar.h"

void	activ_ops(char *arg)
{
	arg[1] == 'd' ? ops.all += D : 0;
	arg[1] == 'l' ? ops.all += L : 0;
	arg[1] == 'n' ? ops.all += N : 0;
	arg[1] == 't' ? ops.all += T : 0;
	arg[1] == 'v' ? ops.all += V : 0;
}


int 	check_options(char *arg)
{
	if(!ft_strchr("dlntv", arg[1]) || !arg[1] || arg[2] != 0) 
		disp_usage(-1, arg);
	activ_ops(arg);
	if(arg[1] == 'l' || arg[1] == 'v')
		return (0);
	return (1);
}


t_dt *check_data(t_dt *dt, char *arg)
{

	int fd;

	if((fd = open(arg, O_RDONLY)) < 0)
	{
		perror(arg);
		disp_usage(0, NULL);
		exit(0);
	}
	if(!chk_magic(fd))
			exit (0);
	dt = get_dt(dt, fd);
	return (dt);
}


void parse(int ac, char ** av, int i, t_dt **dt)
{
	while(++i < ac)
	{
		if(av[i][0] == '-')
			i += check_options(av[i]);
		if(checkops(N))
		{
			is_num(av[i]) ? ops.n = ft_atoi(av[i]) : disp_usage(-2, av[i]);
			is_set(*dt, ops.n) ? ops.all &= 0xfb : 0;
			*dt = check_data(*dt, av[++i]);
			ops.n = 0;
			ops.all &= 0xfb;
		}
		else if(checkops(D))
		{
			is_num(av[i]) ? ops.dump = 0xFFFFFFFF & ft_atoi(av[i]) : disp_usage(-3, av[i]);
			ops.all &= 0xfe;
		}
		else if(checkops(T))
		{
			is_num(av[i]) ? ops.text += 0xff & ft_atoi(av[i]) : disp_usage(-4, av[i]);
			ops.text & 0x10 ? ops.all |= L : 0;
			ops.all &= 0xf7;
		}
		else if (av[i][0] != '-')
			*dt = check_data(*dt, av[i]);
	}	
}

t_dt *parse_args(int ac, char **av)
{
	int 	i;
	t_dt 	*dt;

	i = 0;
	dt = NULL;
 	parse(ac, av, i, &dt);
 	if(ops.all & V)
 	{
 		launch_vizu();
 		refresh();
 	}
	return (dt);
}