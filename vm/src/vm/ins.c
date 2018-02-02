/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:46:22 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 18:46:24 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

void	pause_vm(void)
{
	while (getch() == ERR)
		;
}

void	aff(t_pcs *pcs, t_vm *vm)
{
	int p;

	p = (vm->ram[pcs->pc + 2] - 1) & 0xf;
	p = (pcs->r[p]) % 256;
	g_ops.all & A && p > 32 ? ft_printf("aff: %C\n", p) : 0;
	pcs->pc += 3;
}

void	zjmp(t_pcs *pcs, t_vm *vm)
{
	short	p;
	int		pc;

	(g_ops.text & 1) ? ft_printf("zjmp -") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram, pcs->pc);
	if (pcs->carry)
	{
		pcs->pc = (pc + p % IDX_MOD) & 0x0fff;
		(g_ops.text & 1) ? ft_printf(" %d OK :)", p) : 0;
	}
	else
	{
		pcs->pc += 2;
		(g_ops.text & 1) ? ft_printf("%d FAILED :(", p) : 0;
	}
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void	live(t_pcs *pcs, t_vm *vm)
{
	int		p;
	t_pl	*tmp;

	(g_ops.text & 1) ? ft_printf("live  -") : 0;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_int(vm->ram, pcs->pc);
	(g_ops.text & 1) ? ft_printf(" %d", p) : 0;
	tmp = vm->plst;
	pcs->pc += 4;
	while (tmp)
	{
		if (tmp->player == p)
		{
			++tmp->live;
			vm->last_live = p;
			(g_ops.all & L) ?
			ft_printf("joueur %s : [p %d] IS ALIVE \n", tmp->name, p) : 0;
			g_ops.all & V ? print_alive(tmp->id, tmp->live) : 0;
			break ;
		}
		tmp = tmp->next;
	}
	++pcs->alive;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}
