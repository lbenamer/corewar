/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 03:44:59 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 03:45:00 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_error_label(int id)
{
	if (id == 1)
		ft_printf(GREEN"Usage: "EOC);
	else
		ft_printf(RED"Error: "EOC);
}

void		print_error(int id, char *msg)
{
	print_error_label(id);
	if (id == 1)
		ft_printf("./asm <sourcefile.s>\n");
	else if (id == 2)
		ft_printf("Can't open file: "BOLD YELLOW"%s"EOC"\n", msg);
	else if (id == 3)
		ft_printf("Incorrect filename "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 4)
		ft_printf("Double section "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 5)
		ft_printf("Invalid Name/Comment: "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 6)
		ft_printf("Illegal instruction: "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 7)
		ft_printf("Invalid label name: "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 8)
		ft_printf("Invalid Register: "BOLD YELLOW"%s\n"EOC, msg);
	else if (id == 10)
		ft_printf("%s\n", msg);
	else if (id == 11)
		ft_printf("No newline at end of file\n");
	else if (id == 12)
		ft_printf("Invalid Parameter: "BOLD YELLOW"%s\n"EOC, msg);
	exit(0);
}
