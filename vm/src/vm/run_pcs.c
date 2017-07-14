/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 21:08:36 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/09 21:08:38 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	int				get_cycles(int rd)
{
	int tab[17];

	tab[0] = 0;
	tab[1] = 10;
	tab[2] = 5;
	tab[3] = 5;
	tab[4] = 10;
	tab[5] = 10;
	tab[6] = 6;
	tab[7] = 6;
	tab[8] = 6;
	tab[9] = 20;
	tab[10] = 25;
	tab[11] = 25;
	tab[12] = 800;
	tab[13] = 10;
	tab[14] = 50;
	tab[15] = 1000;
	tab[16] = 2;
	return (tab[rd]);
}

static	void			free_all_pcs(t_pcs *pcs)
{
	ops.text &= 0xfb;
	while (pcs)
		pcs = del_pcs(pcs);
}

static	void			clock(t_pcs *pcs, t_vm *vm, t_ins *ins)
{
	unsigned short lx;

	while (pcs)
	{
		pcs->pc &= 0x0fff;
		lx = vm->ram[pcs->pc];
		if (lx > 0 && lx < 17)
		{
			if (get_cycles(lx) == pcs->cycle)
			{
				ops.all & V ? reverse(pcs->pc, lx, pcs->color) : 0;
				(ops.text & 1) ? printf("P  %5d |", pcs->id) : 0;
				ins[lx](pcs, vm);
				pcs->cycle = 1;
				ops.all & V ? blink_pos(pcs->pc, lx, pcs->color) : 0;
			}
			else
				++pcs->cycle;
		}
		else
		{
			++pcs->pc;
			++pcs->cycle;
		}
		pcs = pcs->prev;
	}
}

static	void			init_ins(t_ins *ins)
{
	ins[0] = NULL;
	ins[1] = &live;
	ins[2] = &ld;
	ins[3] = &st;
	ins[4] = &add;
	ins[5] = &sub;
	ins[6] = &and;
	ins[7] = &or;
	ins[8] = &xor;
	ins[9] = &zjmp;
	ins[10] = &ldi;
	ins[11] = &sti;
	ins[12] = &myfork;
	ins[13] = &lld;
	ins[14] = &lldi;
	ins[0x0F] = &lfork;
	ins[16] = &aff;
}

void				run_pcs(t_pcs *pcs, t_vm *vm)
{
	t_ins	*tb_ins;
	int		n_check;
	int		die;

	die = CYCLE_TO_DIE + 1;
	n_check = 0;
	tb_ins = (t_ins*)ft_memalloc(sizeof(t_ins) * 17);
	init_ins(tb_ins);
	pcs = place_max(pcs);
	while (++vm->cycles && --die >= 0)
	{
		if (ops.dump && vm->cycles == ops.dump + 1)
			return ;
		(ops.text & 2) ? printf("its now cycle : %d\n", vm->cycles) : 0;
		ops.all & V ? print_cycles(vm->cycles) : 0;
		clock(pcs, vm, tb_ins);
		pcs = place_max(pcs);
		if (!die && ++n_check)
			if (!(pcs = check_to_die(pcs, &die, &n_check)))
				break ;
	}
	free(tb_ins);
	free_all_pcs(pcs);
	check_winer(vm);
}
