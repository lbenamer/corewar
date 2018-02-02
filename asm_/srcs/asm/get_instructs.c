/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:31:39 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:31:40 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		get_instructions(t_asm *a, char *line)
{
	char	*first_word;

	first_word = get_first_word(line);
	if (stock_label(first_word, a) == 1)
	{
		if (!(CHECK_BIT(a->bit, LABEL)))
			a->bit |= LABEL;
		line += ft_strlen(first_word);
		stock_opcode(get_first_word(line), a, line);
	}
	else if (!(CHECK_BIT(a->bit, LABEL)))
	{
		a->bit |= LABEL;
		stock_label(ft_strdup("MAIN:"), a);
		get_instructions(a, line);
	}
	else if (stock_opcode(first_word, a, line) == 1)
		return ;
	else
		print_error(10, "");
	free(first_word);
}
