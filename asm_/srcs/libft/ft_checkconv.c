/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkconv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:18:03 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:19:15 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	which_conv(const char *s, int i, t_conv *t)
{
	t->count = 0;
	if (s[i] && s[i + 1])
	{
		i++;
		t->count++;
	}
	while (next_conv(s, i) == 0 && s[i + 1])
	{
		t->count++;
		i++;
	}
	if (next_conv(s, i) == 1)
		t->count--;
	t->conv = next_conv(s, i);
	get_conv(s, t);
}
