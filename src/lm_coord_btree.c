/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_coord_btree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 20:54:02 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/18 22:21:26 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*get_min_nnode(t_room *head)
{
	VAR(t_room*, temp, head);
	while (temp->nleft)
		temp = temp->nleft;
	return (temp);
}

t_room			*lm_name_pop(t_room *head, t_room *del)
{
	if (!head)
		return (head);
	VAR(int, value, ft_strcmp(head->name, del->name));
	if (value > 0)
		head->nleft = lm_name_pop(head->nleft, del);
	else if (value < 0)
		head->nright = lm_name_pop(head->nright, del);
	else
	{
		VAR(t_room*, temp, NULL);
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

void			lm_coord_insert(t_lem *lem, t_room **head, t_room *new)
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
			lm_name_pop(lem->name_head, *head);
			lm_name_pop(lem->name_head, new);
			ft_strdel(&(*head)->name);
			(*head)->name = ft_strdup(new->name);
			(*head)->nleft = NULL;
			(*head)->nright = NULL;
			lm_name_insert(lem, &lem->name_head, *head);
			set_start_end(lem, *head);
			lem->dupe = 1;
		}
		else if (value > 0)
			lm_coord_insert(lem, &(*head)->cleft, new);
		else
			lm_coord_insert(lem, &(*head)->cright, new);
	}
}
