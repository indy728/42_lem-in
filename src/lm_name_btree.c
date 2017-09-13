/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_name_btree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 20:54:02 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/12 18:13:23 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room *get_min_cnode(t_room *head)
{
	t_room *temp;

	temp = head;
	while (temp->cleft)
		temp = temp->cleft;
	return (temp);
}

t_room		 *lm_coord_pop(t_room *head, t_room *del)
{
	int		value;
	t_room	*temp;

	if (!head)
		return (head);
	if (!(value = head->x - del->x))
		value = head->y - del->y;
	if (value > 0)
		head->cleft = lm_coord_pop(head->cleft, del);
	else if (value < 0)
		head->cright = lm_coord_pop(head->cright, del);
	else
	{
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

void		lm_name_insert(t_lem *lem, t_room **head, t_room *new)
{
	VAR(int, value, 0);
	if (*head == NULL)
		*head = new;
	else
		if (!(value = ft_strcmp((*head)->name, new->name)))
		{
			lm_coord_pop(lem->coord_head, *head);
			(*head)->x = new->x;
			(*head)->y = new->y;
		}
		else if (value > 0)
			lm_name_insert(lem, &(*head)->nleft, new);
		else
			lm_name_insert(lem, &(*head)->nright, new);
}

void	lm_destroy_ntree(t_room *root)
{
	if (root)
	{
		lm_destroy_tree(root->nleft);
		lm_destroy_tree(root->nright);
		ft_strdel(&root->name);
		free(root);
		root = NULL;
	}
}

void	lm_clear_ntree(t_room *room)
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

/*void	lm_print_ntree(t_room *room)
{
	if (room)
	{
		if (room->nleft)
			lm_print_ntree(room->nleft);
		ft_printf("%s %d %d\nLinks:\n", room->name, room->x, room->y);
		if (room->links)
		{
			VAR(int, i, -1);
			while (room->links[++i])
				ft_putendl(room->links[i]->name);
		}
		if (room->nright)
			lm_print_ntree(room->nright);
	}
}*/

