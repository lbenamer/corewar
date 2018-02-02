/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 15:53:19 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/14 15:53:22 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

int		chk_magic(int fd)
{
	unsigned int	magic;
	unsigned char	*octet;
	unsigned char	buf[4];

	magic = COREWAR_EXEC_MAGIC;
	read(fd, buf, 4);
	octet = (unsigned char *)&magic;
	octet = mem_rev(octet, 4);
	return (ft_memcmp(octet, buf, 4) ? 0 : 1);
}

char	*get_string(int fd, size_t size)
{
	char	*string;
	char	buf[size];

	read(fd, buf, size);
	string = ft_strnew(ft_strlen(buf));
	ft_strcpy(string, buf);
	return (string);
}

int		get_size(int fd)
{
	unsigned char	buf[4];
	int				ret;
	int				n;
	int				d;

	d = -8;
	ret = 0;
	n = 4;
	read(fd, buf, 4);
	while (--n > -1)
		ret += (0x00 | buf[n] << (d += 8));
	return (ret);
}

char	*get_prog(int fd, unsigned int size)
{
	char *prog;

	prog = (char*)ft_memalloc(sizeof(char) * size);
	if (read(fd, prog, size) != size)
		disp_usage(-5, *g_av);
	return (prog);
}

t_dt	*get_dt(t_dt *dt, int fd)
{
	t_dt		*tmp;
	static int	n = 0;

	if (!dt)
		dt = checkops(N) ? new_dt(fd, g_ops.n) : new_dt(fd, --n);
	else
	{
		if (is_set(dt, n - 1))
			--n;
		tmp = dt;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = checkops(N) ? new_dt(fd, g_ops.n) : new_dt(fd, --n);
		tmp->next->prev = tmp;
	}
	return (dt);
}
