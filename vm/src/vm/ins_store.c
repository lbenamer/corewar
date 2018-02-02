/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 19:24:21 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 19:24:22 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

static	char	*store(char *mem, unsigned char *store, size_t size, size_t add)
{
	size_t i;

	i = -1;
	while (++i < size)
		mem[(add + i) % MEM_SIZE] = store[i];
	return (mem);
}

void			st(t_pcs *pcs, t_vm *vm)
{
	int				p[2];
	int				pc;
	unsigned char	*buf;
	char			opc;

	(g_ops.text & 1) ? ft_printf("st - ") : 0;
	p[0] = 1;
	p[1] = 2;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc +
	load_param(pcs, vm->ram, opc | 0x10, &p[1])) % MEM_SIZE;
	p[1] = (pc + (p[1] % IDX_MOD)) & 0x0fff;
	buf = (unsigned char *)&p[0];
	buf = mem_rev(buf, 4);
	(g_ops.text & 1) ? ft_printf("(with pc and mod: %d)\n", p[1]) : 0;
	store(vm->ram, buf, 4, p[1]);
	if (g_ops.all & V)
		vizu_st(pcs->color, buf, 4, p[1]);
}

void			sti(t_pcs *pcs, t_vm *vm)
{
	int				p[3];
	int				pc;
	unsigned char	*buf;
	char			opc;

	p[0] = 1;
	p[1] = 2;
	p[2] = 3;
	(g_ops.text & 1) ? ft_printf("sti - ") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 64, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 16, &p[1])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc | 4, &p[2])) % MEM_SIZE;
	(g_ops.text & 1) ?
	ft_printf("\n         | -> store to: %d + %d = %d ",
	p[1], p[2], p[1] + p[2]) : 0;
	p[1] = (pc + ((p[1] + p[2]) % IDX_MOD)) & 0x0fff;
	buf = (unsigned char *)&p[0];
	buf = mem_rev(buf, 4);
	store(vm->ram, buf, 4, p[1]);
	(g_ops.all & V) ? vizu_st(pcs->color, buf, 4, p[1]) : 0;
	(g_ops.text & 1) ? ft_printf("(with pc and mod: %d) \n", p[1]) : 0;
}
