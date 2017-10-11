/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:33:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 14:55:08 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant			*lm_antnew(int i, t_queue *path)
{
	VAR(t_ant*, new, (t_ant *)ft_memalloc(sizeof(t_ant)));
	VAR(char*, num, ft_itoa(i));
	new->name = ft_strjoin("L", num);
	new->current = path->next;
	ft_strdel(&num);
	return (new);
}

unsigned int	lm_antcat(t_lem *lem, t_ant *leader, unsigned int ants)
{
	VAR(int, i, -1);
	VAR(t_ant*, tmp, leader);
	VAR(t_head*, path, lem->path_list);
	VAR(int, len, 0);
	while (tmp->next)
		tmp = tmp->next;
	while (path && ants < lem->ants && ++i < lem->path_count)
	{
		if (i && ((int)(lem->ants - ants) / i) < (path->length - len))
			break ;
		tmp->next = lm_antnew(++ants, path->path_head);
		len = path->length;
		path = path->next;
		tmp = tmp->next;
	}
	return (ants);
}

void			lm_antdel(t_ant **leader, t_ant *del)
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
