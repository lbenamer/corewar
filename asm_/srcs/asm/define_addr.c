/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:32:16 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:32:16 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		get_addr(t_opc opc, t_arg *arg, t_asm *a)
{
	t_label *label;

	label = a->label;
	while (label)
	{
		if (!ft_strcmp(arg->name + 2, label->name))
		{
			arg->value = (label->addr > arg->addr) ?
			revert_hex(label->addr - opc.addr, 2) :
			revert_hex(((USHRT_MAX + 1) - (opc.addr - label->addr)), 2);
			arg->l = 0;
		}
		label = label->next;
	}
	if (arg->l == 1)
		print_error(10, "Label not found");
}

static void		stock_addr(t_asm *a)
{
	int		i;
	t_label	*tmp;
	t_opc	*opc;

	tmp = a->label;
	while (tmp)
	{
		if (tmp->opc->name)
		{
			opc = tmp->opc;
			while (opc)
			{
				i = 0;
				while (opc->arg[i].name)
				{
					if (opc->arg[i].l == 1)
						get_addr(*opc, &opc->arg[i], a);
					i++;
				}
				opc = opc->next;
			}
		}
		tmp = tmp->next;
	}
}

static void		clean_name(char *s)
{
	size_t len;

	len = ft_strlen(s);
	if (s[len - 1] == ':')
		s[len - 1] = '\0';
}

static void		split_define_addr(t_opc *opc, unsigned int *count)
{
	int i;

	*count += 1;
	if (opc->need_ocp == 1)
		*count += 1;
	i = 0;
	while (opc->arg[i].name)
	{
		opc->arg[i].addr = *count;
		*count += opc->arg[i].size;
		i++;
	}
}

void			define_addr(t_asm *a)
{
	unsigned int	count;
	t_label			*tmp;
	t_opc			*opc;

	count = 0;
	tmp = a->label;
	while (tmp)
	{
		clean_name(tmp->name);
		tmp->addr = count;
		if (tmp->opc->name)
		{
			opc = tmp->opc;
			while (opc)
			{
				opc->addr = count;
				split_define_addr(opc, &count);
				opc = opc->next;
			}
		}
		tmp = tmp->next;
	}
	a->size = count;
	stock_addr(a);
}
