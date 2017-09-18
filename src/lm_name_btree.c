/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_name_btree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 20:54:02 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/14 20:16:28 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*get_min_cnode(t_room *head)
{
	VAR(t_room*, temp, head);
	while (temp->cleft)
		temp = temp->cleft;
	return (temp);
}

t_room			*lm_coord_pop(t_room *head, t_room *del)
{
	if (!head)
		return (head);
	VAR(int, value, head->x - del->x);
	value = value ? value : head->y - del->y;
	if (value > 0)
		head->cleft = lm_coord_pop(head->cleft, del);
	else if (value < 0)
		head->cright = lm_coord_pop(head->cright, del);
	else
	{
		VAR(t_room*, temp, NULL);
		if (!head->cleft)
		{
			temp = head->cright;
			return (temp);
		}
		else if (!head->cright)
		{
			temp = head->cleft;
			return (temp);
		}
		temp = get_min_cnode(head->cright);
		head->cright = lm_coord_pop(head->cright, temp);
	}
	return (head);
}

void			lm_name_insert(t_lem *lem, t_room **head, t_room *new)
{
	if (*head == NULL)
		*head = new;
	else
	{
		VAR(int, value, 0);
		if (!(value = ft_strcmp((*head)->name, new->name)))
		{
			if (!lem->no_coords)
				lm_coord_pop(lem->coord_head, *head);
			(*head)->x = new->x;
			(*head)->y = new->y;
			(*head)->cleft = NULL;
			(*head)->cright = NULL;
			if (!lem->no_coords)
				lm_coord_insert(lem, &lem->coord_head, *head);
		}
		else if (value > 0)
			lm_name_insert(lem, &(*head)->nleft, new);
		else
			lm_name_insert(lem, &(*head)->nright, new);
	}
}

void			lm_destroy_tree(t_room *root)
{
	if (root)
	{
		lm_destroy_tree(root->nleft);
		lm_destroy_tree(root->nright);
		ft_strdel(&root->name);
		lm_qdel(&root->links);
		free(root);
		root = NULL;
	}
}

void			lm_clear_ntree(t_room *room)
{
	if (room)
	{
		if (room->nleft)
			lm_clear_ntree(room->nleft);
		room->prev = NULL;
		if (room->nright)
			lm_clear_ntree(room->nright);
	}
}
