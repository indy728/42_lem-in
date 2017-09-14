/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_farm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 23:40:28 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/13 21:51:02 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lm_farmadd(t_farm **head, t_farm *new)
{
	if (*head && new)
	{
		if ((*head)->prev)
		{
			VAR(t_farm*, last, (*head)->prev);
			last->next = new;
			new->prev = last;
		}
		else
		{
			(*head)->next = new;
			new->prev = *head;
		}
		(*head)->prev = new;
		new->next = *head;
	}
	else if (new)
		*head = new;
}

t_farm	*lm_farmnew(char *str)
{
	VAR(t_farm*, new, (t_farm *)ft_memalloc(sizeof(t_farm)));
	new->inst = ft_strdup(str);
	return (new);
}

void	lm_farmdel(t_lem *lem)
{
	VAR(t_farm*, head, lem->farm_head);
	if (head)
	{
		VAR(t_farm*, del, head);
		VAR(t_farm*, tmp, NULL);
		if (del->prev)
			del->prev->next = NULL;
		while (del)
		{
			tmp = del;
			del = del->next;
			ft_strdel(&tmp->inst);
			free(tmp);
		}
		head = NULL;
	}
}
