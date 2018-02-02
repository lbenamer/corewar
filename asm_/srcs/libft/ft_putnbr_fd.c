/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:22:17 by aboudjem          #+#    #+#             */
/*   Updated: 2017/03/29 06:18:22 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_putlnbr_fd(unsigned long int n, int fd)
{
	if (n < 10)
		ft_putchar_fd((char)n + 48, fd);
	else if (n >= 10)
	{
		ft_putlnbr_fd(n / 10, fd);
		ft_putlnbr_fd(n % 10, fd);
	}
}

void	ft_putnbr_fd(long int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	if (n < 0 && n > -2147483648)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n < 10 && n > -2147483648)
		ft_putchar_fd((char)n + 48, fd);
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
