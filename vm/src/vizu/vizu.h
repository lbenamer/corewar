/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 00:39:58 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/18 00:40:00 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZU_H
# define VIZU_H
# include <ncurses.h>

typedef struct		s_win
{
	int	startx;
	int	starty;
	int	height;
	int	width;
}					t_win;

WINDOW				*g_box_vm;
WINDOW				*g_box_ram;
WINDOW				*g_box_title;
/*
**launch.c
*/
void				launch_vizu(void);
WINDOW				*init_title(void);
WINDOW				*init_ram(void);
WINDOW				*init_vm(void);
void				print_pause(void);
/*
**create_win.c
*/
void				print_title(WINDOW *win);
WINDOW				*create_box(t_win init, int bd);
void				print_vm(WINDOW *win);
void				print_ram(WINDOW *win);
void				print_player(t_pl *pl);
/*
**print.c
*/
void				print_alive(int id, int live);
void				print_npcs(int npcs);
void				print_die(int die);
void				print_cycles(int cycle);
void				print_finish(void);
/*
**print_.c
*/
void				print_winner(char *name, int id);
void				blink_pos(int add, unsigned short blink, int color);
void				vizu_print_mem(unsigned char *buf, size_t size, size_t add);
void				vizu_print_pgm(t_dt *dt);
void				vizu_st(int color, unsigned char *buf, size_t size,
					size_t add);
void				reverse(int add, unsigned short blink, int color);
#endif
