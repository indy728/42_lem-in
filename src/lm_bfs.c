/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:55:53 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 14:50:57 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_head		*lm_pathfinder(t_lem *lem)
{
	VAR(t_head*, node, (t_head *)ft_memalloc(sizeof(t_head)));
	VAR(t_queue*, head, lm_qnew(lem->end));
	VAR(t_room*, room, head->room);
	VAR(int, n, 0);
	lem->start->prev = NULL;
	while (room != lem->start)
	{
		++n;
		lm_qadd(&head, lm_qnew(room->prev));
		room = head->room;
		room->used = 1;
	}
	node->path_head = head;
	node->length = n;
	lm_clear_ntree(lem->name_head);
	if (!lem->min_length)
		lem->min_length = n;
	lem->end->prev = NULL;
	return (node);
}

void		lm_addpath(t_lem *lem)
{
	++lem->path_count;
	lm_headcat(&lem->path_list, lm_pathfinder(lem));
}

/*
**	cwn: current working node
*/

void		lm_links_loop(t_lem *lem, t_room *cwn, t_queue **head, int *len)
{
	VAR(t_queue*, tmp, NULL);
	VAR(t_room*, node, NULL);
	tmp = cwn->links;
	while (tmp)
	{
		node = tmp->room;
		if (!node->prev && !node->used)
		{
			node->prev = cwn;
			lm_qcat(head, lm_qnew(node));
			if (node == lem->end)
			{
				lm_addpath(lem);
				*len = 0;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

char		lm_bfs(t_lem *lem)
{
	VAR(t_queue*, head, lm_qnew(lem->start));
	VAR(t_room*, cwn, NULL);
	VAR(int, len, 1);
	while (head && lem->path_count < (int)lem->max_paths && lem->min_length != 1)
	{
		cwn = head->room;
		lm_links_loop(lem, cwn, &head, &len);
		lm_qdelhead(&head);
		if (!len)
		{
			lm_qdel(&head);
			head = lm_qnew(lem->start);
		}
		++len;
	}
	lm_qdel(&head);
	return (lem->path_count ? 1 : 0);
}
