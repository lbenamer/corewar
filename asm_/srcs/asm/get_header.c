/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:27 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:27 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		check_name(char *line)
{
	if (ft_strlen(line) > 128)
		print_error(10, "Champion name too long (Max length 128)");
}

static void		check_comment(char *line)
{
	if (ft_strlen(line) > 2048)
		print_error(10, "Champion comment too long (Max length 2048)");
}

static void		get_name(char *line, t_asm *a)
{
	ft_bzero(a->header.prog_name, PROG_NAME_LENGTH);
	if (!(CHECK_BIT(a->bit, NAME)))
		a->bit |= NAME;
	else
		print_error(4, NAME_CMD_STRING);
	line = clean_str(line);
	check_name(line);
	ft_strcpy(a->header.prog_name, get_str(line));
}

static void		get_comment(char *line, t_header *header, t_asm *a)
{
	ft_bzero(header->comment, COMMENT_LENGTH);
	if (!(CHECK_BIT(a->bit, COMM)))
		a->bit |= COMM;
	else
		print_error(4, COMMENT_CMD_STRING);
	line = clean_str(line);
	check_comment(line);
	ft_strcpy(header->comment, get_str(line));
}

void			get_name_and_comment(char *line, t_asm *a)
{
	if (!(ft_strncmp(line, NAME_CMD_STRING, 5)))
		get_name(line + 5, a);
	else if (!(ft_strncmp(line, COMMENT_CMD_STRING, 8)))
		get_comment(line + 8, &a->header, a);
	if ((CHECK_BIT(a->bit, NAME) && CHECK_BIT(a->bit, COMM)))
		a->bit |= SIZE;
	else if (ft_strncmp(line, NAME_CMD_STRING, 5) &&
		ft_strncmp(line, COMMENT_CMD_STRING, 5))
		if (ft_strlen(line) != 0 && line[0] != '#')
			print_error(5, "");
}
