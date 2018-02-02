/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_opc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:04 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:05 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_opc	*new_opc(t_opc opcode, t_arg *args)
{
	t_opc *opc;

	if (!(opc = (t_opc*)ft_memalloc(sizeof(t_opc))))
		print_error(10, "Malloc failed");
	opc->name = ft_strdup(opcode.name);
	opc->opcode = ft_strdup(opcode.opcode);
	opc->need_ocp = opcode.need_ocp;
	opc->label_size = opcode.label_size;
	opc->arg = args;
	opc->next = NULL;
	opc->back = NULL;
	return (opc);
}

void	add_opc(t_opc *opc, t_opc opcode, t_arg *args)
{
	t_opc *tmp;

	if (!opc->name)
	{
		opc->name = ft_strdup(opcode.name);
		opc->opcode = ft_strdup(opcode.opcode);
		opc->need_ocp = opcode.need_ocp;
		opc->arg = args;
	}
	else
	{
		tmp = opc;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_opc(opcode, args);
		tmp->next->back = tmp;
	}
}
