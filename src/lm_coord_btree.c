/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_coord_btree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 20:54:02 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/23 18:59:09 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room *get_min_nnode(t_room *head)
{
	t_room *temp;

	temp = head;
	while (temp->nleft)
		temp = temp->nleft;
	return (temp);
}

t_room		 *lm_name_pop(t_room *head, t_room *del)
{
	int		value;
	t_room	*temp;

	if (!head)
		return (head);
	value = ft_strcmp(head->name, del->name);
	if (value > 0)
		head->nleft = lm_name_pop(head->nleft, del);
	else if (value < 0)
		head->nright = lm_name_pop(head->nright, del);
	else
	{
		if (!head->nleft)
		{
			temp = head->nright;
			return (temp);
		}
		else if (!head->nright)
		{
			temp = head->nleft;
			return (temp);
		}
		temp = get_min_nnode(head->nright);
		head->nright = lm_name_pop(head->nright, temp);
	}
	return (head);
}

void		lm_coord_insert(t_lem *lem, t_room **head, t_room *new)
{
	VAR(int, value, 0);
	if (*head == NULL)
		*head = new;
	else
	{
		if (!(value = (*head)->x - new->x))
			value = (*head)->y - new->y;
		if (!value)
		{
			lm_name_pop(lem->name_head, new);
			lm_name_pop(lem->name_head, *head);
			(*head)->name = new->name;
			lm_name_insert(lem, &lem->name_head, *head);
		}
		else if (value > 0)
			lm_coord_insert(lem, &(*head)->cleft, new);
		else
			lm_coord_insert(lem, &(*head)->cright, new);
	}
}

void	lm_destroy_tree(t_room *root)
{
	if (root)
	{
		lm_destroy_tree(root->cleft);
		lm_destroy_tree(root->cright);
		ft_strdel(&root->name);
		free(root);
		root = NULL;
	}
}

void	lm_print_ctree(t_room *room)
{
	if (room)
	{
		if (room->cleft)
			lm_print_ctree(room->cleft);
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		if (room->cright)
			lm_print_ctree(room->cright);
	}
}

