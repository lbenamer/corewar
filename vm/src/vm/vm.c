/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 00:33:03 by lbenamer          #+#    #+#             */
/*   Updated: 2017/07/15 00:33:05 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../vizu/vizu.h"

t_pcs			*del_pcs(t_pcs *pcs)
{
	t_pcs *tmp_next;
	t_pcs *tmp_prev;

	tmp_next = pcs->next;
	tmp_prev = pcs->prev;
	if (pcs->prev)
	{
		free_pcs(pcs);
		pcs = tmp_prev;
		pcs->next = tmp_next;
		if (tmp_next)
			tmp_next->prev = pcs;
	}
	else if (pcs->next)
	{
		free_pcs(pcs);
		pcs = tmp_next;
		pcs->prev = NULL;
	}
	else
	{
		free_pcs(pcs);
		return (NULL);
	}
	return (pcs);
}

t_pcs			*check_alive(t_pcs *pcs, int *total)
{
	while (pcs)
	{
		if (!pcs->alive)
		{
			(g_ops.text & 4) ?
			ft_printf(RED"Process %d has been destroyed\n"STOP, pcs->id) : 0;
			if (!(pcs = del_pcs(pcs)))
			{
				(g_ops.text & 4) ? ft_printf("all process are dead \n") : 0;
				return (NULL);
			}
		}
		else if (pcs->prev)
		{
			*total += pcs->alive;
			pcs->alive = 0;
			pcs = pcs->prev;
		}
		else
		{
			*total += pcs->alive;
			return (pcs);
		}
	}
	return (pcs);
}

t_pcs			*check_to_die(t_pcs *pcs, int *die, int *n_check)
{
	static int	cycle_to_die = CYCLE_TO_DIE;
	int			total;

	total = 0;
	if (!(pcs = check_alive(pcs, &total)))
		return (NULL);
	pcs = place_max(pcs);
	if (total >= NBR_LIVE || *n_check == MAX_CHECKS)
	{
		cycle_to_die -= CYCLE_DELTA;
		*die = cycle_to_die;
		g_ops.all & V ? print_die(*die) : 0;
		*n_check = 0;
	}
	else
		*die = cycle_to_die;
	(g_ops.text & 8) ? ft_printf("die is now = %d\n", *die) : 0;
	if (*die < 0)
		return (NULL);
	return (pcs);
}

void			check_winer(t_vm *vm)
{
	t_pl *pl;

	pl = vm->plst;
	while (pl)
	{
		if (pl->player == vm->last_live)
		{
			g_ops.all & V ? print_winner(pl->name, pl->id) :
			ft_printf(GREEN"Player %s [ %d ] Won The Game\n"STOP,
			pl->name, pl->player);
			break ;
		}
		pl = pl->next;
	}
}
