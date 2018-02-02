/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:22:40 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:22:43 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_start(t_conv *t)
{
	t->i = 0;
	t->j = 0;
}

char	next_conv(const char *s, int i)
{
	int		j;
	char	*conv;

	j = 0;
	conv = "sdiuc";
	while (conv[j] != '\0')
	{
		if (s[i] == conv[j])
			return (conv[j]);
		j++;
	}
	return (0);
}

void	init(t_conv *t)
{
	t->len_return = 0;
}
