/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 21:31:23 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/18 20:52:27 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		lm_remove_path_list(t_lem *lem)
{
	VAR(t_head*, del, lem->path_list);
	VAR(t_head*, tmp, NULL);
	VAR(t_head*, head, NULL);
	while (del)
	{
		tmp = del;
		lm_qdel(&del->path_head);
		del = tmp->next;
		free(tmp);
	}
	lem->path_list = NULL;
}

void		lm_delete(t_lem *lem)
{
	lm_remove_path_list(lem);
	lm_farmdel(lem);
	ft_strdel(&lem->errstr);
	lm_destroy_tree(lem->name_head);
	free(lem);
}

void		lm_headcat(t_head **head, t_head *new)
{
	if (*head)
	{
		VAR(t_head*, scout, *head);
		while (scout->next)
			scout = scout->next;
		scout->next = new;
	}
	else
		*head = new;
}
