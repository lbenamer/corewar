/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:33 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:34 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		get_name(char *line, t_header *header, t_asm *a)
{
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	if (!(CHECK_BIT(a->bit, NAME)))
		a->bit |= NAME;
	else
		print_error(4, "");
	ft_strcpy(header->prog_name, get_str(line));
}

static void		get_comment(char *line, t_header *header, t_asm *a)
{
	ft_bzero(header->comment, COMMENT_LENGTH);
	if (!(CHECK_BIT(a->bit, COMM)))
		a->bit |= COMM;
	else
		print_error(4, "");
	ft_strcpy(header->comment, get_str(line));
}

void			get_infos(char *line, t_header *header, t_asm *a)
{
	header->magic = COREWAR_EXEC_MAGIC;
	if (!(ft_strncmp(line, NAME_CMD_STRING, 5)))
		get_name(line, header, a);
	else if (!(ft_strncmp(line, COMMENT_CMD_STRING, 5)))
		get_comment(line, header, a);
	else if ((CHECK_BIT(a->bit, NAME) && CHECK_BIT(a->bit, COMM)))
		a->bit |= SIZE;
	else if (ft_strncmp(line, NAME_CMD_STRING, 5) &&
			ft_strncmp(line, COMMENT_CMD_STRING, 5))
		if (ft_strlen(line) != 0 && line[0] != '#')
			print_error(5, "");
}
