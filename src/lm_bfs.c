/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:55:53 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/24 00:01:59 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_path(t_list *begin_list, t_lem *lem)
{
	t_list	*node;

	node = begin_list;
	VAR(t_room*, room, (t_room *)node->content);
	if (!begin_list)
		return ;
	while (ft_strcmp(room->name, lem->end->name))
	{
		ft_printf("%s->", room->name);
		node = node->next;
		room = (t_room *)node->content;
	}
	ft_printf("%s\n", room->name);
}

static t_list	*lm_pathfinder(t_lem *lem)
{
	VAR(t_list*, begin_list, ft_lstnew(lem->end, sizeof(t_room)));
	VAR(t_room*, room, (t_room *)begin_list->content);
	while (ft_strcmp(room->name, lem->start->name))
	{
		ft_lstadd(&begin_list, ft_lstnew(room->prev, sizeof(t_room)));
		room = (t_room *)begin_list->content;
	}
	print_path(begin_list, lem);
	return (begin_list);
}

/*
**	cwn: current working node
*/

t_list	*lm_bfs(t_lem *lem)
{
	VAR(t_list*, begin_list, ft_lstnew(lem->start, sizeof(t_room)));
	VAR(t_list*, tmp, NULL);
	VAR(t_room*, cwn, NULL);
	VAR(int, i, -1);
	VAR(int, found, 0);
	while (begin_list && !found)
	{
		cwn = (t_room *)begin_list->content;
		while (cwn->links[++i])
		{
			if (cwn->links[i]->prev == NULL && cwn->links[i] != lem->start)
			{
				cwn->links[i]->prev = cwn;
				ft_lstcat(&begin_list, ft_lstnew(cwn->links[i], sizeof(t_room)));
				if (!ft_strcmp(cwn->links[i]->name, lem->end->name))
				{
					++found;
					break ;
				}
			}
		}
		tmp = begin_list;
		begin_list = begin_list->next;
		free (tmp);
		i = -1;
	}
	ft_lstdel(&begin_list, free); 
	return (found ? lm_pathfinder(lem) : NULL);
}
