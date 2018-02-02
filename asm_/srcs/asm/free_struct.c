/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 00:49:30 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 00:51:07 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_arg_structure(t_arg *arg)
{
	free(arg->name);
	free(arg);
}

void	free_opc_structure(t_opc *opc)
{
	int i;

	i = 0;
	free(opc->name);
	free(opc->opcode);
	if (opc->arg)
		while (opc->arg[i].name)
			free_arg_structure(&opc->arg[i++]);
}

void	free_label_structure(t_label *label)
{
	free(label->name);
	while (label->opc)
	{
		free_opc_structure(label->opc);
		label->opc = label->opc->next;
	}
	free(label);
}

void	free_asm_structure(t_asm *a)
{
	free(a->filename);
	while (a->label)
	{
		free_label_structure(a->label);
		a->label = a->label->next;
	}
}
