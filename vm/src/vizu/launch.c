/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 23:48:24 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 23:48:26 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/corewar.h"
#include "vizu.h"

void		launch_vizu(void)
{
	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
	assume_default_colors(COLOR_WHITE, COLOR_BLACK);
	g_box_ram = init_ram();
	g_box_title = init_title();
	g_box_vm = init_vm();
	print_title(g_box_title);
	print_ram(g_box_ram);
	print_vm(g_box_vm);
	refresh();
}

WINDOW		*init_title(void)
{
	WINDOW	*win;
	t_win	title;

	title.height = LINES / 10;
	title.width = COLS - 6;
	title.startx = 3;
	title.starty = 0;
	win = create_box(title, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

WINDOW		*init_ram(void)
{
	WINDOW	*win;
	t_win	ram;

	ram.height = LINES - (LINES / 10) - 1;
	ram.width = COLS - (COLS / 4) - 4;
	ram.startx = 3;
	ram.starty = LINES / 10;
	win = create_box(ram, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

WINDOW		*init_vm(void)
{
	WINDOW	*win;
	t_win	vm;

	vm.height = LINES - (LINES / 10) - 1;
	vm.width = (COLS / 4) - 3;
	vm.startx = COLS - ((COLS / 4));
	vm.starty = LINES / 10;
	win = create_box(vm, ' ');
	refresh();
	wrefresh(win);
	return (win);
}

void		print_pause(void)
{
	char	*s;
	int		x;
	int		y;

	getmaxyx(g_box_vm, y, x);
	wattron(g_box_vm, COLOR_PAIR(1) | A_BOLD);
	s = "** PRESS ANY KEY TO PAUSE **";
	mvwprintw(g_box_vm, 27, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(g_box_vm, COLOR_PAIR(1) | A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}
