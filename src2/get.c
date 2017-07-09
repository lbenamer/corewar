#include "corewar.h"

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
	int n;
	int d = -8;

	read(fd, buf, 4);
	ret = 0;
	n = 4;
	while(--n > -1)
		ret += (0x00 | buf[n] << (d += 8));
	// ret = (ret | buf[3]);
	// ret += ((0x00 |  buf[2]) << 8);
	// ret += (0x00 | buf[1]) << 16;
	// ret += (0x00 | buf[0]) << 24;	
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
	static int n = -1;

	if(!dt)
	{
		dt = checkops(N) ? new_dt(fd, ops.n) : new_dt(fd, n);
		if(!checkops(V))
			printf("Player: [ %d ] - Size : %d oct - Name: %s -> %s \n",dt->player, dt->size, dt->name, dt->com);
	}
	else
	{
		if(is_set(dt, n))
			--n;
		tmp = dt;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = checkops(N) ? new_dt(fd, ops.n) : new_dt(fd, n);
		if(!checkops(V))
			printf("Player: [ %d ] - Size : %d oct - Name: %s -> %s \n",
		tmp->next->player, tmp->next->size, tmp->next->name, tmp->next->com);
		tmp->next->prev = tmp;
	}
	return (dt);
}
