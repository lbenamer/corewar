#include "corewar.h"

int					is_set(t_dt *dt, int n)
{
	t_dt *tmp;
	tmp = dt;
	while (tmp)
	{
		if (tmp->player == n)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int					is_num(char *str)
{
	int i;

	i = 0;

	while (str[i] == ' ')
		++i;
	(str[0] == '-' || str[0] == '+') ? ++i : 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void				init_ops(t_option *ops)
{
	ops->all = 0;
	ops->text = 0;
	ops->dump = 0;
	ops->n = 0;
}

void				print_mem(char *str, size_t n)
{
	size_t i;

	i = -1;
	ft_printf("0x%.4x : ", 0);
	while (++i < n)
	{
		if (((i % 64) == 0) && i)
		{
			ft_printf("\n");
			ft_printf("0x%.4zx : ", i);
		}
		ft_printf("%.2hhx ", str[i]);
	}
	ft_printf("\n");
}

unsigned char		*mem_rev(unsigned char *mem, int n)
{
	char tmp;
	int i;

	i = 0;
	int nb = n;
	while (--n >= nb / 2)
	{
		tmp = mem[i];
		mem[i++] = mem[n];
		mem[n] = tmp;
	}
	return (mem);
}
