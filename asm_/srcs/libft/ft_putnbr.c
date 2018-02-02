/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:20:53 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:20:54 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_putnbr(int n)
{
	long int	u_nbr;

	u_nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		u_nbr = -n;
	}
	if (u_nbr / 10)
		ft_putnbr((int)(u_nbr / 10));
	ft_putchar(u_nbr % 10 + '0');
}
