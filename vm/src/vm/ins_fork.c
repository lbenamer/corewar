/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:50:45 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 18:50:47 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

static	t_pcs	*new_fork(t_pcs *src, int id, int pc)
{
	t_pcs	*pcs;
	int		i;

	i = 0;
	g_nbr_pcs += 1;
	pcs = (t_pcs*)ft_memalloc(sizeof(t_pcs));
	pcs->r = (int*)ft_memalloc(sizeof(int) * 16);
	pcs->carry = src->carry;
	pcs->alive = src->alive;
	pcs->color = src->color;
	pcs->id = id;
	pcs->pc = pc;
	pcs->cycle = 1;
	pcs->next = NULL;
	pcs->prev = NULL;
	while (i < 16)
	{
		pcs->r[i] = src->r[i];
		i++;
	}
	g_ops.all & V ? print_npcs(g_nbr_pcs) : 0;
	return (pcs);
}

void			myfork(t_pcs *pcs, t_vm *vm)
{
	int		p;
	t_pcs	*new;
	t_pcs	*tmp;
	int		pc;

	(g_ops.text & 1) ? ft_printf("myfork  -") : 0;
	tmp = pcs;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram, pcs->pc);
	(g_ops.text & 1) ? ft_printf(" %d", p) : 0;
	p = (pc + p % IDX_MOD) & 0x0fff;
	(g_ops.text & 1) ? ft_printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 2;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void			lfork(t_pcs *pcs, t_vm *vm)
{
	int		p;
	t_pcs	*new;
	t_pcs	*tmp;
	int		pc;

	(g_ops.text & 1) ? ft_printf("lfork  -") : 0;
	pc = pcs->pc;
	tmp = pcs;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	p = get_short(vm->ram, pcs->pc);
	(g_ops.text & 1) ? ft_printf(" %d", p) : 0;
	p = (pc + p) & 0x0fff;
	(g_ops.text & 1) ? ft_printf(" with pc and mod : %d ", p) : 0;
	tmp = place_max(pcs);
	new = new_fork(pcs, tmp->id + 1, p);
	tmp->next = new;
	tmp->next->prev = tmp;
	pcs->pc += 2;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}
