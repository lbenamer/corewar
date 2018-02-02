/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 22:54:13 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/29 22:57:11 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		init_asm_structure(t_asm *a)
{
	a->bit = 0;
	a->label = (t_label*)ft_memalloc(sizeof(t_label));
	a->label->opc = (t_opc*)ft_memalloc(sizeof(t_opc));
	a->label->name = NULL;
	a->label->next = NULL;
	a->check = init_optab();
}

void		init_check(t_check *check, char *name, char *opcode, size_t size)
{
	check->name = name;
	check->opcode = opcode;
	check->size = size;
}

void		init_check2(t_check *check, char *mod, int ocp, int label_size)
{
	check->mod = mod;
	check->need_ocp = ocp;
	check->label_size = label_size;
}

t_check		*init_optab(void)
{
	t_check *tab;

	if (!(tab = (t_check	*)malloc(sizeof(t_check) * 16)))
		exit(-1);
	init_check(&tab[0], "live", "\x1", 1);
	init_check2(&tab[0], LIVE, 0, 4);
	init_check(&tab[1], "ld", "\x2", 2);
	init_check2(&tab[1], LD, 1, 4);
	init_check(&tab[2], "st", "\x3", 2);
	init_check2(&tab[2], ST, 1, 0);
	init_check(&tab[3], "add", "\x4", 3);
	init_check2(&tab[3], ADD, 1, 0);
	init_check(&tab[4], "sub", "\x5", 3);
	init_check2(&tab[4], SUB, 1, 0);
	init_check(&tab[5], "and", "\x6", 3);
	init_check2(&tab[5], AND, 1, 4);
	init_check(&tab[6], "or", "\x7", 3);
	init_check2(&tab[6], OR, 1, 4);
	init_check(&tab[7], "xor", "\x8", 3);
	init_check2(&tab[7], XOR, 1, 4);
	init_optab2(tab);
	return (tab);
}

t_check		*init_optab2(t_check *tab)
{
	init_check(&tab[8], "zjmp", "\x9", 1);
	init_check2(&tab[8], ZJMP, 0, 2);
	init_check(&tab[9], "ldi", "\xA", 3);
	init_check2(&tab[9], LDI, 1, 2);
	init_check(&tab[10], "sti", "\xB", 3);
	init_check2(&tab[10], STI, 1, 2);
	init_check(&tab[11], "fork", "\xC", 1);
	init_check2(&tab[11], FORK, 0, 2);
	init_check(&tab[12], "lld", "\xD", 2);
	init_check2(&tab[12], LLD, 1, 4);
	init_check(&tab[13], "lldi", "\xE", 3);
	init_check2(&tab[13], LLDI, 1, 2);
	init_check(&tab[14], "lfork", "\xF", 1);
	init_check2(&tab[14], LFORK, 0, 2);
	init_check(&tab[15], "aff", "\x10", 1);
	init_check2(&tab[15], AFF, 1, 0);
	return (tab);
}
