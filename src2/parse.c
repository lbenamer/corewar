#include "corewar.h"

void disp_usage(int error, char *arg)
{
	// ft_printf(YELLOW);
	if(error == -1)
		ft_printf("illegal option : %s\n", arg);
	if(error == -2)
		ft_printf("illegal player id : %s\n", arg);
	if(error == -3)
		ft_printf("illegal dump number : %s\n", arg);
	if(error == -4)
		ft_printf("illegal Text mode : %s\n", arg);
	ft_printf("./corewar [ -d N | -l | -t N | -v ] | [ -n N ] </path/champ.cor> <...>\n");
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
	// ft_printf(STOP);
	exit(0);
}

void	activ_ops(char *arg)
{
	arg[1] == 'd' ? ops.all += D : 0;
	arg[1] == 'l' ? ops.all += L : 0;
	arg[1] == 'n' ? ops.all += N : 0;
	arg[1] == 't' ? ops.all += T : 0;
	arg[1] == 'v' ? ops.all += V : 0;
}

//void activ_text_ops(char *arg);


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

int is_set(t_dt *dt, int n)
{
	t_dt *tmp;
	tmp = dt;
	while(tmp)
	{
		if(tmp->player == n)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int is_num(char *str)
{
	int i;

	i = 0;

	while(str[i] == ' ')
		++i;
	(str[0] == '-' || str[0] == '+') ? ++i : 0;
	while(str[i])
		if(!ft_isdigit(str[i++]))
			return (0);
	return (1);
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
	return (dt);
}