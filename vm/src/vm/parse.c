/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 16:23:56 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/14 16:23:59 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

void			activ_ops(char *arg)
{
	arg[1] == 'd' ? g_ops.all |= D : 0;
	arg[1] == 'l' ? g_ops.all |= L : 0;
	arg[1] == 'n' ? g_ops.all |= N : 0;
	arg[1] == 't' ? g_ops.all |= T : 0;
	arg[1] == 'v' ? g_ops.all |= V : 0;
	arg[1] == 'a' ? g_ops.all |= A : 0;
}

int				check_options(char *arg)
{
	if (!ft_strchr("adlntv", arg[1]) || !arg[1] || arg[2] != 0)
		disp_usage(-1, arg);
	activ_ops(arg);
	if (arg[1] == 'l' || arg[1] == 'v')
		return (0);
	++g_av;
	return (1);
}

t_dt			*check_data(t_dt *dt, char *arg)
{
	int fd;

	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		ft_printf(RED);
		perror(arg);
		disp_usage(0, NULL);
	}
	if (!chk_magic(fd))
		disp_usage(-6, arg);
	dt = get_dt(dt, fd);
	return (dt);
}

void			parse(int ac, char **av, int i, t_dt **dt)
{
	while (++i < ac && av[i] && ++g_av)
	{
		av[i][0] == '-' ? i += check_options(av[i]) : 0;
		if (checkops(N) && av[i])
		{
			isnum(av[i]) ? g_ops.n = ft_atoi(av[i]) : disp_usage(-2, av[i]);
			is_set(*dt, g_ops.n) ? g_ops.all &= 0xfb : 0;
			*dt = check_data(*dt, av[++i]);
			g_ops.n = 0;
			g_ops.all &= 0xfb;
		}
		else if (checkops(D) && av[i])
		{
			isnum(av[i]) ? g_ops.dump = ft_atoi(av[i]) : disp_usage(-3, av[i]);
			g_ops.all &= 0xfe;
		}
		else if (checkops(T) && av[i])
		{
			isnum(av[i]) ? g_ops.text += ft_atoi(av[i]) : disp_usage(-4, av[i]);
			g_ops.text & 0x10 ? g_ops.all |= L : 0;
			g_ops.all &= 0xf7;
		}
		else if (av[i] && av[i][0] != '-')
			*dt = check_data(*dt, av[i]);
	}
}

t_dt			*parse_args(int ac, char **av)
{
	int		i;
	t_dt	*dt;

	i = 0;
	dt = NULL;
	parse(ac, av, i, &dt);
	if (g_ops.all & V)
	{
		g_ops.all = V;
		g_ops.text = 0;
	}
	!(g_ops.all & V) ? disp_player(dt) : 0;
	return (dt);
}
