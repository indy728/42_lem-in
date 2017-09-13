/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:39:25 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/12 16:28:31 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_queue		*lm_qnew(t_room *room)
{
	VAR(t_queue*, new, (t_queue *)ft_memalloc(sizeof(t_queue)));
	if (!new)
		return (NULL);
	new->room = room;
	return (new);
}

void		lm_qcat(t_queue **head, t_queue *new)
{
	if (*head)
	{
		VAR(t_queue*, scout, *head);
		while (scout->next)
			scout = scout->next;
		scout->next = new;
	}
	else
		*head = new;
}

void		lm_qdelhead(t_queue **head)
{
	if (*head)
	{
		VAR(t_queue*, tmp, *head);
		*head = tmp->next;
		free(tmp);
	}
}

void		lm_qdel(t_queue **head)
{
	while (*head)
		lm_qdelhead(head);
}

void		lm_qadd(t_queue **head, t_queue *new)
{
	if (new)
		new->next = *head;
	*head = new;
}
