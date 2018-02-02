/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:58 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:59 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_str(char *line)
{
	char	*tmp;
	size_t	len;

	tmp = (line + 1);
	len = ft_strlen(tmp);
	if (tmp[len - 1] == '"')
		tmp[len - 1] = '\0';
	return (tmp);
}

int		get_nb(char *str)
{
	int	i;
	int j;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	j = i;
	while (str[i] != '\0')
	{
		if ((ft_isdigit(str[i])) == 0 || (i - j) >= 10)
			return (0);
		i++;
	}
	return (ft_atoi(str));
}

void	remove_comment(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

char	*get_first_word(char *line)
{
	unsigned int i;
	unsigned int start;

	i = 0;
	start = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	return (ft_strsub(line, start, i - start));
}

char	*remove_opcode(char *instruction)
{
	int i;

	i = 0;
	while (instruction[i] && instruction[i] != ' ' && instruction[i] != '\t')
		i++;
	return (instruction + i);
}
