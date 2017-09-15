/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 21:31:23 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/14 17:54:18 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		lm_remove_path_list(t_lem *lem)
{
	VAR(t_list*, del, lem->path_list);
	VAR(t_list*, tmp, NULL);
	VAR(t_head*, head, NULL);
	while (del)
	{
		tmp = del;
		head = (t_head *)del->content;
		lm_qdel(&head->path_head);
		free(head);
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