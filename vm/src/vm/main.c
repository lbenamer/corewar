/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 16:04:32 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/14 16:04:36 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

static void		init_t_vm(t_vm *vm)
{
	vm->cycles = 0;
	vm->last_live = 0;
	vm->plst = new_pl(0, NULL, NULL, 1);
	vm->ram = (char*)ft_memalloc(sizeof(char) * MEM_SIZE);
}

int				main(int ac, char **av)
{
	t_dt	*dt;
	t_vm	vm;
	t_pcs	*pcs;
	int		n;

	if (ac < 2)
		disp_usage(0, NULL);
	g_av = av;
	g_nbr_pcs = 0;
	init_ops(&g_ops);
	init_t_vm(&vm);
	pcs = new_pcs(0, 0, 1, 1);
	if (!(dt = parse_args(ac, av)))
		disp_usage(0, NULL);
	n = load_ram(dt, vm.ram);
	load_pcs_plst(dt, pcs, vm.plst, n);
	if (g_ops.all & V)
		display_start(dt, vm.plst);
	nodelay(stdscr, TRUE);
	run_pcs(pcs, &vm);
	nodelay(stdscr, FALSE);
	g_ops.dump && !checkops(V) ? print_mem(vm.ram, MEM_SIZE) : 0;
	if (g_ops.all & V)
		display_finish();
	return (0);
}
