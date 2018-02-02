/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 00:00:25 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/18 00:00:26 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/corewar.h"
#include "vizu.h"

void	print_alive(int id, int live)
{
	int y;

	id == 1 ? y = 12 : 0;
	id == 2 ? y = 16 : 0;
	id == 3 ? y = 20 : 0;
	id == 4 ? y = 24 : 0;
	wattron(g_box_vm, A_BOLD);
	wattron(g_box_vm, COLOR_PAIR(id));
	mvwprintw(g_box_vm, y, 19, "%d", live);
	wattroff(g_box_vm, COLOR_PAIR(id));
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}

void	print_npcs(int npcs)
{
	wattron(g_box_vm, A_BOLD);
	mvwprintw(g_box_vm, 7, 17, "%4d", npcs);
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}

void	print_die(int die)
{
	wattron(g_box_vm, A_BOLD);
	mvwprintw(g_box_vm, 30, 20, "%4d", die);
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}

void	print_cycles(int cycle)
{
	wattron(g_box_vm, A_BOLD);
	mvwprintw(g_box_vm, 5, 14, "%d", cycle);
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}

void	print_finish(void)
{
	char	*s;
	int		x;
	int		y;

	getmaxyx(g_box_vm, y, x);
	s = "** PRESS ANY KEY TO FINISH **";
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	wattron(g_box_vm, A_BOLD);
	wattron(g_box_vm, COLOR_PAIR(5));
	mvwprintw(g_box_vm, 27, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(g_box_vm, COLOR_PAIR(5));
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}
