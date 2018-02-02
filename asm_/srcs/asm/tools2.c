/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:47 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 03:40:05 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				empty_line(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && line[i] != '\0')
	{
		if (line[i] == '#')
			return (1);
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

unsigned int	revert_hex(unsigned int x, size_t bytes)
{
	unsigned char	c1;
	unsigned char	c2;

	if (bytes == 2)
	{
		c1 = (short)x & 255;
		c2 = ((short)x >> 8) & 255;
		return ((unsigned int)(c1 << 8) + c2);
	}
	else if (bytes == 4)
	{
		x = (x >> (unsigned int)24) |
			((x << (unsigned int)8) & 0x00FF0000) |
			((x >> (unsigned int)8) & 0x0000FF00) |
			(x << (unsigned int)24);
	}
	return (x);
}

char			*line_handler(char *line)
{
	char *tmp;

	tmp = NULL;
	remove_comment(line);
	tmp = ft_strtrim(line);
	ft_memdel((void **)&line);
	return (tmp);
}

int				count_char(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

char			*clean_str(char *line)
{
	int i;

	if (!line)
		print_error(5, "");
	if (count_char(line, '"') != 2)
		print_error(5, "Invalid number of \"");
	i = 0;
	while (line[i] && line[i] != '"')
	{
		if (line[i] != '\t' && line[i] != ' ')
			print_error(5, "Invalid char");
		i++;
	}
	check_cmt(line + i);
	return (line + i);
}
