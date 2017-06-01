#include "corewar.h"

t_dt  *new_dt(int fd, int player)
{
	t_dt *dt;

	dt = (t_dt*)ft_memalloc(sizeof(t_dt));
	dt->name = get_string(fd, PROG_NAME_LENGTH + 4);
	dt->size = (unsigned int)get_size(fd);
	dt->com = get_string(fd, COMMENT_LENGTH + 4);
	dt->prog = get_prog(fd, dt->size);
	dt->player = player;
	dt->next = NULL;
	dt->prev = NULL;
	return (dt); 
}

char *get_string(int fd, size_t size)
{
	char *string;
	char buf[size];

	read(fd, buf, size);
	string = ft_strnew(ft_strlen(buf));
	ft_strcpy(string, buf);
	return (string);
}

int get_size(int fd)
{
	unsigned char buf[4];
	int ret;

	read(fd, buf, 4);
	ret = 0x00000000;
	ret = (ret | buf[3]);
	ret += ((0x00 |  buf[2]) << 8);
	ret += (0x00 | buf[1]) << 16;
	ret += (0x00 | buf[0]) << 24;	
	return (ret);
}

char 	*get_prog(int fd, unsigned int size)
{
	char *prog;

	prog = (char*)ft_memalloc(sizeof(char) * size);
	read(fd, prog, size);
	return(prog);
}

t_dt 	*get_dt(t_dt *dt, int fd)
{
	t_dt *tmp;

	if(!dt)
		dt = new_dt(fd, 1);
	else
	{
		tmp = dt;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new_dt(fd, tmp->player + 1);
		tmp->next->prev = tmp;
	}
	return (dt);
}
