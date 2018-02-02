/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:22:12 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:22:14 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strstr(char *big, char *little)
{
	int i;
	int pos;
	int len;

	i = 0;
	pos = 0;
	len = 0;
	while (little[len] != '\0')
		len++;
	if (len == 0)
		return ((char *)big);
	while (big[i])
	{
		while (little[pos] == big[i + pos])
		{
			if (pos == len - 1)
				return (big + i);
			pos++;
		}
		pos = 0;
		i++;
	}
	return (0);
}
