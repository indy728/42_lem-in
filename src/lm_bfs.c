/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:55:53 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/12 18:40:11 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_path(t_queue *head, t_lem *lem)
{
	if (!head)
		return ;
	VAR(t_queue*, node, head);
	while (node->room != lem->end)
	{
		ft_printf("%s->", node->room->name);
		node = node->next;
	}
	ft_printf("%s\n", node->room->name);
}

/*void	clear_paths(t_lem *lem, t_queue *head)
{
	VAR(t_queue*, tmp, head);
	VAR(t_queue*, link, NULL);
	VAR(t_room*, cwn, NULL);
	link = lem->start->links;
	while (link)
	{
		if (link->room != head->next->room)
			link->room->prev = NULL;
		link = link->next;
	}
	while (tmp->next)
	{
		cwn = tmp->room;
		link = cwn->links;
		while (link)
		{
			if (!link->room->used)
				link->room->prev = NULL;
			link = link->next;
		}
		tmp = tmp->next;
	}
}*/

t_head	*lm_pathfinder(t_lem *lem)
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
		room = head->room;;
		room->used = 1;
	}
	node->path_head = head;
	node->length = n;
	print_path(head, lem);
//	clear_paths(lem, head);
	lm_clear_ntree(lem->name_head);
	if (!lem->min_length)
		lem->min_length = n;
	lem->end->prev = NULL;
	return (node);
}

void	lm_addpath(t_lem *lem)
{
	++lem->path_count;
	ft_lstcat(&lem->path_list, ft_lstnew(lm_pathfinder(lem), sizeof(t_head)));
}

/*
**	cwn: current working node
*/

char	lm_bfs(t_lem *lem)
{
	VAR(t_queue*, head, lm_qnew(lem->start));
	VAR(t_queue*, tmp, NULL);
	VAR(t_room*, cwn, NULL);
	VAR(t_room*, node, NULL);
	VAR(int, len, 1);
	while (head && lem->path_count < lem->max_paths/* &&
			lem->ants / ft_max(1, lem->path_count) + lem->min_length >= len*/)
	{
		cwn = head->room;
		tmp = cwn->links;
		while (tmp)
		{
			node = tmp->room;
			if (!node->prev && !node->used)
			{
				node->prev = cwn;
				lm_qcat(&head, lm_qnew(node));
				if (node == lem->end)
				{
					KMDB("FOUND");
					lm_addpath(lem);
					KMDB("PATH ADDED");
					lm_bfs(lem);
				}
			}
			tmp = tmp->next;
		}
		lm_qdelhead(&head);
		++len;
	}
	lm_qdel(&head);
	return (lem->path_count ? 1 : 0);
}
