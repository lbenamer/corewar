/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:52 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:53 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	count_args(t_arg *args)
{
	size_t i;

	i = 0;
	while (args[i].name)
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*file_name(char *name)
{
	char	*filename;
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(name, '/');
	while (tab[i + 1])
		i++;
	if (tab[i] && ft_strstr(tab[i], ".s"))
		filename = ft_strsub(name, 0, ft_strlen(name) - 2);
	else
	{
		free_tab(tab);
		print_error(1, "");
	}
	free_tab(tab);
	return (filename);
}

void	check_cmt(char *line)
{
	int i;

	i = 1;
	while (line[i] && line[i] != '"')
		i++;
	i++;
	while (line[i])
	{
		if (line[i] != '\t' &&
				line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
			print_error(5, "Invalid\n");
		i++;
	}
}
