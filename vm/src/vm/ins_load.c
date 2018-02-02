/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:55:27 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 18:55:29 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

void		lld(t_pcs *pcs, t_vm *vm)
{
	int		p[2];
	char	opc;
	int		pc;

	p[0] = 1;
	(g_ops.text & 1) ? ft_printf("lld  -") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[0])) % MEM_SIZE;
	if (read_opc(opc, 1) == IND_CODE)
	{
		p[0] = (p[0] + pc) & 0x0fff;
		p[0] = get_int(vm->ram, p[0]);
	}
	p[1] = vm->ram[pcs->pc] - 1;
	p[1] &= 0xf;
	pcs->r[p[1]] = p[0];
	pcs->carry = !p[0] ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[1]) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		ld(t_pcs *pcs, t_vm *vm)
{
	int		p[2];
	char	opc;
	int		pc;

	p[0] = 1;
	(g_ops.text & 1) ? ft_printf("ld  -") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc + load_param(pcs, vm->ram, opc, &p[0])) % MEM_SIZE;
	if (read_opc(opc, 1) == IND_CODE)
	{
		p[0] = (pc + p[0] % IDX_MOD) & 0x0fff;
		p[0] = get_int(vm->ram, p[0]);
	}
	p[1] = vm->ram[pcs->pc] - 1;
	p[1] &= 0xf;
	pcs->r[p[1]] = p[0];
	pcs->carry = !p[0] ? 1 : 0;
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf(" r%d", p[1] + 1) : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		lldi(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;
	int		pc;

	p[0] = 1;
	p[1] = 2;
	(g_ops.text & 1) ? ft_printf("lldi  -") : 0;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc +
	load_param(pcs, vm->ram, opc | 0x40, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc +
	load_param(pcs, vm->ram, opc | 0x10, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	p[0] = (p[0] + p[1] + pc) & 0x0fff;
	(g_ops.text & 1) ? ft_printf("with pc and mod %d,", p[0]) : 0;
	p[0] = get_int(vm->ram, p[0]);
	pcs->r[p[2]] = p[0];
	pcs->pc += 1;
	pcs->carry = !p[0] ? 1 : 0;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}

void		ldi(t_pcs *pcs, t_vm *vm)
{
	int		p[3];
	char	opc;
	int		pc;

	(g_ops.text & 1) ? ft_printf("ldi  -") : 0;
	p[0] = 1;
	p[1] = 2;
	pc = pcs->pc;
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	opc = vm->ram[pcs->pc];
	pcs->pc = (pcs->pc + 1) % MEM_SIZE;
	pcs->pc = (pcs->pc +
	load_param(pcs, vm->ram, opc | 0x40, &p[0])) % MEM_SIZE;
	pcs->pc = (pcs->pc +
	load_param(pcs, vm->ram, opc | 0x10, &p[1])) % MEM_SIZE;
	p[2] = vm->ram[pcs->pc] - 1;
	p[2] &= 0xf;
	p[0] += p[1];
	p[0] = (pc + p[0] % IDX_MOD) & 0x0fff;
	(g_ops.text & 1) ? ft_printf("with pc and mod %d,", p[0]) : 0;
	p[0] = get_int(vm->ram, p[0]);
	pcs->r[p[2]] = p[0];
	pcs->pc += 1;
	(g_ops.text & 1) ? ft_printf("\n") : 0;
}
