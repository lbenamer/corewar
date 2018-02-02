/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:22:36 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:24:13 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_strtrim(char *s)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0')
		return (ft_strdup(s));
	end = ft_strlen(s) - 1;
	while (s[start] && (s[start] == ' ' || s[start] == '\t'
				|| s[start] == '\n'))
		start++;
	while (end && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'))
		end--;
	if (start == ft_strlen(s))
		return (ft_strnew(0));
	return (ft_strsub(s, start, end - start + 1));
}
