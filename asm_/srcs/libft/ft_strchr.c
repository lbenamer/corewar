/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:21:18 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:21:20 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char*)s;
	while (s[i] && s[i] != c)
		i++;
	if (str[i] == c)
		return (str + i);
	return (NULL);
}
