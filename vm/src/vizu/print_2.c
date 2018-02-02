/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 00:18:12 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/18 00:18:14 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/corewar.h"
#include "vizu.h"

void		vizu_st(int color, unsigned char *buf, size_t size, size_t add)
{
	wattron(g_box_ram, COLOR_PAIR(color) | A_BOLD);
	vizu_print_mem(buf, size, add);
	wattroff(g_box_ram, COLOR_PAIR(color) | A_BOLD);
}
