/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:30:58 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:01 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*new_label(char *str)
{
	t_label *label;

	if (!(label = (t_label*)ft_memalloc(sizeof(t_label))))
		print_error(10, "Malloc failed");
	label->name = ft_strdup(str);
	label->next = NULL;
	label->back = NULL;
	if (!(label->opc = (t_opc*)ft_memalloc(sizeof(t_opc))))
		print_error(10, "Malloc failed");
	label->opc->next = NULL;
	return (label);
}

void		add_label(t_label *label, char *str)
{
	t_label *tmp;

	if (!label->name)
		label->name = ft_strdup(str);
	else
	{
		tmp = label;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_label(str);
		tmp->next->back = tmp;
	}
}
