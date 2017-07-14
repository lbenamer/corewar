/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:30:35 by lbenamer          #+#    #+#             */
/*   Updated: 2016/11/29 06:31:36 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char *ft_strjoin_free(char *s1, char *s2)
{
	char *new;

	if(!s1 && !s2)
		return (NULL);
	if(!(new = (char*)malloc(sizeof(char) * ft_strlen_p(s1) + ft_strlen_p(s2) + 1)))
		return (NULL);
	if(!s1)
	{
		new = ft_strcpy(new, s2);
		return (new);
	}
	ft_strcpy(new,s1);
	free(s1);
	s1 = NULL;
	if(!s2)
		return (new);
	ft_strcat(new, s2);
	return (new);
}

static char	*ft_strsub_free(char *s, size_t start, size_t len)
{
	char    *sub;
	size_t  i;

	if (!s || !s[start] || !len)
	{
		ft_strdel(&s);
	 	return (NULL);
	}
	sub = (char*)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < len)
		sub[i] = s[i + start];
	sub[i] = '\0';
	ft_strdel(&s);
	return (sub);
}

int		get_next_line(int fd, char **line)
{
	size_t i;
	char buf[BUFF_SIZE + 1];
	static char *s = 0;

	i = -1;
	ft_bzero(buf, BUFF_SIZE);
	if((read(fd, buf, BUFF_SIZE)) == -1 || fd < 0)
		return (-1);
	if(ft_strlen_p(buf))
		s = ft_strjoin_free(s, buf);
	if(!(s))
		return (0);
	if(!ft_strchr(s, '\n') && ft_strlen_p(buf))
		return(get_next_line(fd, line));
	while(s[++i] != '\n' && s[i])
			;
	*line = ft_strsub(s, 0, i);
	s[i] == '\n' ? s = ft_strsub_free(s, i + 1, ft_strlen(s) - i + 1) :
	ft_strdel(&s);
	return(1);
}