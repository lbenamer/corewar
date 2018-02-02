/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdig_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:19:56 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:19:57 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_isdig_str(char *ptr)
{
	unsigned int i;

	i = 0;
	while (ptr[i])
	{
		if (!ft_isdigit(ptr[i]))
			return (0);
		++i;
	}
	return (1);
}