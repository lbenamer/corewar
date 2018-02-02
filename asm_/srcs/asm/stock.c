/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 22:29:53 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/29 22:31:33 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_arg	*split_args(char *parameters)
{
	int		i;
	t_arg	*tmp;
	char	**tab;

	i = 0;
	tmp = NULL;
	if (!(tab = ft_strsplit(parameters, SEPARATOR_CHAR)))
		print_error(10, "Malloc failed");
	if (!(tmp = (t_arg*)malloc(sizeof(t_arg) *
		(unsigned int)(tab_len(tab) + 1))))
		print_error(10, "Malloc failed");
	while (tab[i])
	{
		if (!empty_line(tab[i]))
			tmp[i].name = ft_strtrim(tab[i]);
		i++;
	}
	tmp[i].name = NULL;
	free_tab(tab);
	return (tmp);
}

void	add_opc_to_label(t_label *l, t_opc opcode, t_arg *args)
{
	while (l->next)
		l = l->next;
	add_opc(l->opc, opcode, args);
}

t_arg	*stock_args(t_asm *a, char *instruction, char *line)
{
	t_arg *args;

	instruction = remove_opcode(instruction);
	args = split_args(instruction);
	check_arguments(a, args, line);
	return (args);
}

int		stock_opcode(char *name, t_asm *a, char *line)
{
	t_opc	opcode;
	int		index;
	char	*instruc;

	if (name[ft_strlen(name) - 1] != LABEL_CHAR)
	{
		if ((index = is_a_valid_opcode(a, name)) != -1)
		{
			opcode.name = ft_strdup(a->check[index].name);
			opcode.opcode = ft_strdup(a->check[index].opcode);
			opcode.need_ocp = a->check[index].need_ocp;
			opcode.label_size = a->check[index].label_size;
			opcode.arg = NULL;
			instruc = ft_strtrim(line);
			add_opc_to_label(a->label, opcode, stock_args(a, instruc, line));
			free(instruc);
			free(opcode.name);
			free(opcode.opcode);
			free(name);
			return (1);
		}
		if (!empty_line(name))
			print_error(6, name);
	}
	return (0);
}

int		stock_label(char *str, t_asm *a)
{
	if (str[ft_strlen(str) - 1] == LABEL_CHAR)
	{
		if ((CHECK_BIT(a->bit, LABEL) || is_a_valid_label(str)))
		{
			add_label(a->label, str);
			return (1);
		}
		else
			ft_printf("[Bien?]-\n");
		print_error(7, str);
	}
	return (0);
}
