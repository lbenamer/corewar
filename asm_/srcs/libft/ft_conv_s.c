/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:30:19 by aboudjem          #+#    #+#             */
/*   Updated: 2017/03/09 01:32:22 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	conv_s(t_conv *t)
{
	if (!t->s)
	{
		ft_putstr_fd("(null)", t->fd);
		exit(1);
	}
	else
	{
		ft_putstr_fd(t->s, t->fd);
		t->len_return = (int)ft_strlen(t->s);
	}
}
