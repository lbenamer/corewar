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

void		print_winner(char *name, int id)
{
	size_t x;
	size_t y;

	getmaxyx(g_box_vm, y, x);
	wattron(g_box_vm, A_BOLD);
	mvwprintw(g_box_vm, 40, (x - 11) / 2, "** PLAYER **");
	wattron(g_box_vm, COLOR_PAIR(id));
	mvwprintw(g_box_vm, 42, (x - ft_strlen(name)) / 2, "%s", name);
	wattroff(g_box_vm, COLOR_PAIR(id));
	mvwprintw(g_box_vm, 44, (x - 20) / 2, "!!! WON THE GAME !!!");
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}

void		reverse(int add, unsigned short blink, int color)
{
	size_t x;
	size_t y;
	size_t stx;

	getmaxyx(g_box_ram, y, x);
	stx = (x - 192) / 2;
	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;
	wattron(g_box_ram, COLOR_PAIR(color) | A_REVERSE | A_BOLD);
	mvwprintw(g_box_ram, y, x, "%.2hhx", blink);
	wattroff(g_box_ram, A_DIM | COLOR_PAIR(color) | A_REVERSE | A_BOLD);
	refresh();
	wrefresh(g_box_ram);
}

void		blink_pos(int add, unsigned short blink, int color)
{
	size_t x;
	size_t y;
	size_t stx;

	getmaxyx(g_box_ram, y, x);
	stx = (x - 192) / 2;
	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;
	wattron(g_box_ram, COLOR_PAIR(color) | A_BOLD);
	mvwprintw(g_box_ram, y, x, "%.2hhx", blink);
	wattroff(g_box_ram, COLOR_PAIR(color) | A_BOLD);
	refresh();
	wrefresh(g_box_ram);
}

void		vizu_print_pgm(t_dt *dt)
{
	int		add;
	int		part;
	int		color;
	t_dt	*tmp;

	add = 0;
	color = 1;
	tmp = dt;
	part = MEM_SIZE / nb_process(dt);
	i_color();
	while (tmp)
	{
		wattron(g_box_ram, COLOR_PAIR(color));
		vizu_print_mem((unsigned char*)tmp->prog, tmp->size, add);
		wattroff(g_box_ram, COLOR_PAIR(color));
		add += part;
		++color;
		tmp = tmp->next;
	}
}

void		vizu_print_mem(unsigned char *buf, size_t size, size_t add)
{
	size_t x;
	size_t y;
	size_t stx;
	size_t i;

	getmaxyx(g_box_ram, y, x);
	stx = (x - 192) / 2;
	x = (add % 64) * 3 + stx;
	y = (add / 64) % 64;
	i = 0;
	while (i < size)
	{
		mvwprintw(g_box_ram, y, x, "%.2hhx ", buf[i++]);
		x += 3;
		if (x > stx + 190)
		{
			++y;
			x = stx;
		}
		y %= 64;
	}
	refresh();
	wrefresh(g_box_ram);
}
