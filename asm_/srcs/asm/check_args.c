/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:10 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:11 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_direct_size(t_arg *arg, t_check *check, int index)
{
	if (arg->name[0] != DIRECT_CHAR)
		print_error(10, "Wrong Direct char");
	arg->l = (arg->name[1] == LABEL_CHAR) ? 1 : 0;
	return (check[index].label_size);
}

static char		check_type(char *param)
{
	if (is_a_valid_register(param))
		return ('R');
	else if (is_a_valid_direct(param))
		return ('D');
	else if (is_a_valid_indirect(param))
		return ('I');
	else
		print_error(12, param);
}

static void		get_arg_size(t_arg *arg, t_check *check, int index)
{
	if (arg->type == 'R')
	{
		arg->size = 1;
		arg->value = (unsigned int)ft_atoi(arg->name + 1);
	}
	else if (arg->type == 'I')
	{
		arg->size = IND_SIZE;
		if (!(arg->value = (unsigned)get_nb(arg->name)) && arg->name[0] != ':')
			if (ft_strcmp(arg->name, "0"))
				print_error(10, "Invalid Indirect");
		arg->value = revert_hex(arg->value, 2);
	}
	else if (arg->type == 'D')
	{
		arg->size = (size_t)get_direct_size(arg, check, index);
		if (!(arg->value = (unsigned)get_nb(arg->name + 1)) &&
				arg->name[1] != ':')
			if (ft_strcmp(arg->name + 1, "0"))
				print_error(10, "Invalid Direct");
		arg->value = revert_hex(arg->value, arg->size);
	}
}

static void		check_valid_args(t_asm *a, t_arg *arg, int index)
{
	char	**checker;
	size_t	i;

	i = 0;
	checker = ft_strsplit(a->check[index].mod, ',');
	while (i < a->check[index].size)
	{
		if (!(ft_strchr(checker[i], (arg[i].type = (check_type(arg[i].name))))))
			print_error(8, arg[i].name);
		get_arg_size(&arg[i], a->check, index);
		i++;
	}
	ft_free_tab(checker);
}

void			check_arguments(t_asm *a, t_arg *arg, char *line)
{
	int		i;
	int		index;
	char	*first_word;

	index = 0;
	while (1)
	{
		first_word = get_first_word(line);
		if (!ft_strcmp(a->check[index].name, first_word))
			break ;
		index++;
		free(first_word);
	}
	free(first_word);
	i = 0;
	if (!(count_args(arg) == a->check[index].size))
		print_error(8, "Arguments error\n");
	check_valid_args(a, arg, index);
	a->bit |= READ;
}
