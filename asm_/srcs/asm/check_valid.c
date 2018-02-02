/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:14 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:15 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	is_a_valid_opcode(t_asm *a, char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(a->check[i].name, opcode))
			return (i);
		i++;
	}
	return (-1);
}

int	is_a_valid_label(char *label)
{
	unsigned long i;

	i = 0;
	while (i < ft_strlen(label) - 1)
	{
		if (ft_findchar(LABEL_CHARS, label[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	is_a_valid_register(char *str)
{
	int reg;

	if (str[0] != 'r')
		return (0);
	if (ft_strlen(str + 1) == 0)
		print_error(8, str);
	reg = get_nb(str + 1);
	if (reg < 1 || reg > REG_NUMBER)
		print_error(8, str);
	return (1);
}

int	is_a_valid_direct(char *direct)
{
	if (direct[0] != DIRECT_CHAR)
		return (0);
	direct++;
	if (direct[0] && direct[0] == ':')
	{
		direct++;
		if (!(is_a_valid_label(direct)))
			return (0);
	}
	return (1);
}

int	is_a_valid_indirect(char *indirect)
{
	if (indirect[0] == DIRECT_CHAR)
		return (0);
	indirect++;
	if (indirect[0] && indirect[0] == ':')
	{
		indirect++;
		if (!(is_a_valid_label(indirect)))
			return (0);
	}
	return (1);
}
