#include "libft.h"

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
		line = ft_memalloc((unsigned int)i + ft_strlen_p(tmp) + 1);
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

// size_t  ft_strlen_p(const char *s)
// {
// 	size_t i;

// 	i = 0;
// 	if(s)
// 		while(s[i])
// 			i++;
// 	return (i);
// }

// char *ft_strjoin_free(char *s1, char *s2)
// {
// 	char *new;

// 	if(!(new = (char*)malloc(sizeof(char) * ft_strlen_p(s1) + ft_strlen_p(s2) + 1)))
// 		return (NULL);
// 	if(!s1)
// 	{
// 		new = ft_strcpy(new, s2);
// 		return (new);
// 	}
// 	if(!s2)
// 	{
// 		new = ft_strcpy(new, s1);
// 		return (new);
// 	}
// 	ft_strcpy(new,s1);
// 	ft_strcat(new, s2);
// 	ft_strdel(&s1);
// 	return (new);
// }

// char	*ft_strsub_free(char *s, size_t start, size_t len)
// {
// 	char    *sub;
// 	size_t  i;

// 	if (!s)
// 		return (NULL);
// 	sub = (char*)malloc(sizeof(char) * len + 1);
// 	if (!sub)
// 		return (NULL);
// 	i = -1;
// 	while (++i < len)
// 		sub[i] = s[i + start];
// 	sub[i] = '\0';
// 	ft_strdel(&s);
// 	return (sub);
// }

// int		get_next_line(int fd, char **line)
// {
// 	size_t i;
// 	char *buf;
// 	static char *s = 0;

// 	i = -1;
// 	buf = ft_strnew(BUFF_SIZE);
// 	if((read(fd, buf, BUFF_SIZE)) == -1 || fd < 0)
// 		return (-1);
// 	 s = ft_strjoin_free(s, buf);
// 	if(!ft_strlen(s))
// 		return (0);
// 	if(!ft_strchr(s, '\n') && ft_strlen(buf))
// 	{
// 		ft_strdel(&buf);
// 		return(get_next_line(fd, line));
// 	}
// 	while(s[++i] != '\n' && s[i])
// 		ft_strdel(&buf);
// 	line[0] = ft_strsub(s, 0, i);
// 	s[i] != '\n' ? s = ft_strnew(1) : 0;
// 	s[i] == '\n' ? s = ft_strsub_free(s, i + 1, ft_strlen(s) - i + 1) : 0;
// 	return(1);
// }


















