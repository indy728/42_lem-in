/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:33:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/14 16:37:16 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*lm_antnew(t_lem *lem, int i, t_queue *path)
{
	VAR(t_ant*, new, (t_ant *)ft_memalloc(sizeof(t_ant)));
	VAR(char*, num, ft_itoa(i));
	new->name = ft_strjoin("L", num);
	new->current = path->next;
	ft_strdel(&num);
	return (new);
}

int		lm_antcat(t_lem *lem, t_ant *leader, int ants)
{
	VAR(int, i, -1);
	VAR(t_ant*, tmp, leader);
	VAR(t_list*, path, lem->path_list);
	VAR(t_head*, head, NULL);
	VAR(int, len, 0);
	while (tmp->next)
		tmp = tmp->next;
	while (path && ants < lem->ants && ++i < lem->path_count)
	{
		head = ((t_head *)(path->content));
		if (i && ((lem->ants - ants) / i) < (head->length - len))
			break ;
		tmp->next = lm_antnew(lem, ++ants, head->path_head);
		len = head->length;
		path = path->next;
		tmp = tmp->next;
	}
	return (ants);
}

void	lm_antdel(t_ant **leader, t_ant *del)
{
	VAR(t_ant*, tmp, del);
	if (*leader == del)
		*leader = (*leader)->next;
	else
	{
		VAR(t_ant*, new, *leader);
		while (new->next != del)
			new = new->next;
		new->next = del->next;
	}
	ft_strdel(&tmp->name);
	free(tmp);
}
