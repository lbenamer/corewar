/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 19:05:14 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 19:05:16 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

void		sub(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;

	p[0] = 1;
	p[1] = 2;
	(g_ops.text & 1) ? ft_printf("sub -") : 0;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x10, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] - p[1];
	pcs->carry = !(pcs->r[p[2]]) ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[2] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		add(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;

	p[0] = 1;
	p[1] = 2;
	(g_ops.text & 1) ? ft_printf("add  -") : 0;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x40, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, 0x10, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] + p[1];
	pcs->carry = !(pcs->r[p[2]]) ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[2] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		and(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;

	(g_ops.text & 1) ? ft_printf("and  -") : 0;
	p[0] = 1;
	p[1] = 2;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] & p[1];
	pcs->carry = !(pcs->r[p[2]]) ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[2] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		or(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;

	(g_ops.text & 1) ? ft_printf("or -") : 0;
	p[0] = 1;
	p[1] = 2;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] | p[1];
	pcs->carry = !(pcs->r[p[2]]) ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[2] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		xor(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;

	(g_ops.text & 1) ? ft_printf("xor  -") : 0;
	p[0] = 1;
	p[1] = 2;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	pcs->r[p[2]] = p[0] ^ p[1];
	pcs->carry = !(pcs->r[p[2]]) ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[2] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}
