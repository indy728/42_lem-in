/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_add_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 22:28:03 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/18 21:51:19 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			set_start_end(t_lem *lem, t_room *new)
{
	if (lem->start_next)
	{
		lem->start = new;
		lem->start_next = 0;
	}
	else if (lem->end_next)
	{
		lem->end = new;
		lem->end_next = 0;
	}
}

static void		dupe_room(t_lem *lem, t_room *new)
{
	lem->dupe = 0;
	ft_strdel(&new->name);
	free(new);
}

void			add_room(t_lem *lem, char **room)
{
	VAR(t_room*, new, NULL);
	new = (t_room *)ft_memalloc(sizeof(t_room));
	new->name = ft_strdup(room[0]);
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->prev = NULL;
	new->links = NULL;
	new->nleft = NULL;
	new->nright = NULL;
	new->cleft = NULL;
	new->cright = NULL;
	set_start_end(lem, new);
	lm_name_insert(lem, &lem->name_head, new);
	if (!lem->no_coords)
		lm_coord_insert(lem, &lem->coord_head, new);
	if (lem->dupe)
		dupe_room(lem, new);
}

static t_room	*find_node(t_room *head, char *name)
{
	VAR(int, value, 0);
	if (!head)
		return (NULL);
	value = ft_strcmp(head->name, name);
	if (!value)
		return (head);
	if (value > 0)
		return (find_node(head->nleft, name));
	else
		return (find_node(head->nright, name));
}

int				add_link(t_lem *lem, char **link)
{
	VAR(t_room*, link1, find_node(lem->name_head, link[0]));
	VAR(t_room*, link2, find_node(lem->name_head, link[1]));
	if (!link1 || !link2)
		return (1 - lm_err_str(lem, ERR6));
	if (link1 == link2)
		return (1 - lm_err_str(lem, ERR10));
	lm_qadd(&link1->links, lm_qnew(link2));
	lm_qadd(&link2->links, lm_qnew(link1));
	return (1);
}
