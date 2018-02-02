/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:22:48 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:22:50 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char		*fill_line(char *line, char *buf)
{
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	j = 0;
	tmp = line;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!line)
		line = ft_memalloc((unsigned int)i + 1);
	else
		line = ft_memalloc((unsigned int)i + ft_strlen(tmp) + 1);
	i = -1;
	while (tmp[++i])
		line[i] = tmp[i];
	while (buf[j] && buf[j] != '\n')
	{
		line[i] = buf[j];
		i++;
		j++;
	}
	free(tmp);
	return (line);
}

static void		multi_fd(t_struct **gnl, int fd)
{
	t_struct	*tmp;

	while ((*gnl)->prev != NULL && (*gnl)->fd != fd)
		*gnl = (*gnl)->prev;
	while ((*gnl)->next != NULL && (*gnl)->fd != fd)
		*gnl = (*gnl)->next;
	if ((*gnl)->fd != fd)
	{
		tmp = *gnl;
		(*gnl)->next = ft_memalloc(sizeof(t_struct) + 1);
		*gnl = (*gnl)->next;
		(*gnl)->s1 = ft_memalloc(BUFF_SIZE + 1);
		(*gnl)->s2 = NULL;
		(*gnl)->next = NULL;
		(*gnl)->prev = tmp;
		(*gnl)->fd = fd;
	}
}

static int		go_malloc(t_struct **gnl, char **line, int fd)
{
	*line = ft_memalloc(1);
	if (!*gnl)
	{
		if (!(*gnl = (t_struct *)ft_memalloc(sizeof(t_struct) + 1)))
			return (0);
		if (!((*gnl)->s1 = ft_memalloc(BUFF_SIZE + 1)))
			return (0);
		(*gnl)->s2 = NULL;
		(*gnl)->fd = fd;
		(*gnl)->next = NULL;
		(*gnl)->prev = NULL;
		return (1);
	}
	if ((*gnl)->fd != fd)
		multi_fd(gnl, fd);
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static t_struct		*gnl = NULL;
	int					rd;

	rd = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	go_malloc(&gnl, line, fd);
	while (gnl->s2 || (rd = (int)read(fd, gnl->s1, BUFF_SIZE)))
	{
		if (gnl->s2)
		{
			*line = fill_line(*line, gnl->s2 + 1);
			if ((gnl->s2 = ft_strchr(gnl->s2 + 1, '\n')) != NULL)
				return (1);
			if (!(rd = (int)read(fd, gnl->s1, BUFF_SIZE)))
				return (0);
		}
		if (rd < 0)
			return (-1);
		gnl->s1[rd] = '\0';
		*line = fill_line(*line, gnl->s1);
		if ((gnl->s2 = ft_strchr(gnl->s1, '\n')))
			return (1);
	}
	return ((rd || **line) ? 1 : 0);
}
