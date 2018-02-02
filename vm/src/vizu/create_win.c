/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 23:34:18 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/17 23:34:20 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/corewar.h"
#include "vizu.h"

void			print_title(WINDOW *win)
{
	int		x;
	int		y;
	int		hd;
	char	*line;

	getmaxyx(win, y, x);
	y = 0;
	wattron(win, COLOR_PAIR(1));
	hd = open("./vm/.header_m42.txt", O_RDONLY);
	while (get_next_line(hd, &line) > 0)
	{
		mvwprintw(win, y, x / 2 - (ft_strlen(line) / 2), "%s", line);
		free(line);
		line = NULL;
		++y;
	}
	wattroff(win, COLOR_PAIR(1));
	refresh();
	wrefresh(win);
}

WINDOW			*create_box(t_win init, int bd)
{
	WINDOW *win;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	win = newwin(init.height, init.width, init.starty, init.startx);
	wattron(win, COLOR_PAIR(1));
	box(win, bd, bd);
	wattroff(win, COLOR_PAIR(1));
	refresh();
	wrefresh(win);
	return (win);
}

void			print_vm(WINDOW *win)
{
	int		x;
	int		y;
	char	*s;

	getmaxyx(win, y, x);
	wattron(win, A_BOLD);
	s = "** VIRTUAL MACHINE **";
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 2, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(win, COLOR_PAIR(1));
	mvwprintw(win, 5, 5, "Cycles : 0");
	mvwprintw(win, 7, 5, "Processes : ");
	s = "** PRESS ANY KEY TO START **";
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 27, (x - ft_strlen(s)) / 2, "%s", s);
	wattroff(win, COLOR_PAIR(1));
	mvwprintw(win, 30, 5, "CYCLE_TO_DIE : %4d", CYCLE_TO_DIE);
	mvwprintw(win, 32, 5, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(win, 34, 5, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(win, 36, 5, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(win, A_BOLD);
	refresh();
	wrefresh(win);
}

void			print_ram(WINDOW *win)
{
	int	i;
	int	j;
	int	x;
	int	y;

	getmaxyx(win, y, x);
	y = x;
	j = -1;
	while (++j < 64)
	{
		i = -1;
		x = (y - 192) / 2;
		while (++i < 64)
		{
			mvwprintw(win, j, x, "%.2hhx ", 0);
			x += 3;
		}
	}
	refresh();
	wrefresh(win);
}

void			print_player(t_pl *pl)
{
	int		y;
	int		color;
	t_pl	*tmp;

	tmp = pl;
	y = 10;
	color = 1;
	wattron(g_box_vm, A_BOLD);
	while (tmp)
	{
		mvwprintw(g_box_vm, y, 5, "Player :");
		wattron(g_box_vm, COLOR_PAIR(color));
		mvwprintw(g_box_vm, y, 14, "%s", tmp->name);
		wattroff(g_box_vm, COLOR_PAIR(color));
		mvwprintw(g_box_vm, y + 1, 10, "Number : %d", tmp->player);
		mvwprintw(g_box_vm, y + 2, 10, "lives  : 0");
		++color;
		y += 4;
		tmp = tmp->next;
	}
	wattroff(g_box_vm, A_BOLD);
	refresh();
	wrefresh(g_box_vm);
}
