/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:21:34 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:21:35 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		exit(0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
