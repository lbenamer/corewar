/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 22:44:43 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 03:38:44 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				create_binary_file(char *name, t_asm *a)
{
	int fd;

	a->filename = ft_strjoin(file_name(name), ".cor");
	a->header.magic = revert_hex(COREWAR_EXEC_MAGIC, 4);
	if (!(fd = open(a->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)))
		print_error(2, "");
	write_file(fd, *a);
	ft_printf("Writing output program to"GREEN" %s\n"EOC, a->filename);
}

static int			calcul_ocp(char ocp)
{
	if (ocp == 'R')
		return (64);
	else if (ocp == 'D')
		return (128);
	else if (ocp == 'I')
		return (192);
	else
		exit(0);
}

static int			get_ocp(t_arg *args)
{
	int ocp;

	ocp = 0;
	if (args[0].name)
		ocp += calcul_ocp(args[0].type);
	if (args[1].name)
	{
		if (args[1].type == 'R')
			ocp += 16;
		else if (args[1].type == 'D')
			ocp += 32;
		else if (args[1].type == 'I')
			ocp += 48;
	}
	if (args[2].name)
	{
		if (args[2].type == 'R')
			ocp += 4;
		else if (args[2].type == 'D')
			ocp += 8;
		else if (args[2].type == 'I')
			ocp += 12;
	}
	return (ocp);
}

void				write2_file(int fd, t_asm *a)
{
	int i;
	int ocp;

	i = 0;
	ocp = 0;
	write(fd, a->label->opc->opcode, 1);
	if (a->label->opc->need_ocp == 1)
	{
		ocp = get_ocp(a->label->opc->arg);
		write(fd, (char*)&ocp, 1);
	}
	i = 0;
	while (a->label->opc->arg[i].name)
	{
		write(fd, (char*)&a->label->opc->arg[i].value,
				a->label->opc->arg[i].size);
		i++;
	}
}

void				write_file(int fd, t_asm a)
{
	define_addr(&a);
	a.header.prog_size = revert_hex(a.size, 4);
	write(fd, (&a.header), sizeof(t_header));
	while (a.label)
	{
		if (a.label->opc->name)
			while (a.label->opc)
			{
				write2_file(fd, &a);
				if (a.label->opc->next == NULL)
					break ;
				a.label->opc = a.label->opc->next;
			}
		if (a.label->next == NULL)
			break ;
		a.label = a.label->next;
	}
}
