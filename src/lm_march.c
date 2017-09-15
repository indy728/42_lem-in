/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_march.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 01:02:05 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/14 17:50:54 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lm_ant_advance(t_lem *lem, t_ant **leader)
{
	VAR(t_ant*, line, *leader);
	VAR(t_ant*, del, NULL);
	VAR(int, ret, 0);
	while (line)
	{
		del = line;
		line->current = line->current->next;
		line = line->next;
		if (!del->current)
		{
			lm_antdel(leader, del);
			++ret;
		}
	}
	return (ret);
}

void	lm_antprint(t_lem *lem, t_ant *leader)
{
	VAR(t_ant*, line, leader);
	while (line->next)
	{
		ft_printf("%s-%s ", line->name, line->current->room->name);
		line = line->next;
	}
	ft_printf("%s-%s\n", line->name, line->current->room->name);
	++lem->turn_count;
}

void	lm_onestep(t_lem *lem)
{
	VAR(int, i, 0);
	VAR(char*, name, NULL);
	VAR(char*, tmp, NULL);
	while (++i < lem->ants)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin("L", tmp);
		ft_printf("%s-%s ", name, lem->end->name);
		ft_strdel(&name);
		ft_strdel(&tmp);
	}
	tmp = ft_itoa(i);
	name = ft_strjoin("L", tmp);
	ft_printf("%s-%s\n", name, lem->end->name);
	ft_strdel(&name);
	ft_strdel(&tmp);
	lem->turn_count = 1;
}

int		list_init(t_lem *lem, t_ant **leader)
{
	VAR(int, i, 0);
	VAR(t_list*, path, lem->path_list);
	VAR(t_head*, head, (t_head *)(path->content));
	VAR(int, len, lem->min_length);
	*leader = lm_antnew(lem, ++i, head->path_head);
	VAR(t_ant*, tmp, *leader);
	while (path && i < lem->ants && i < lem->path_count)
	{
		path = path->next;
		head = (t_head *)path->content;
		if ((lem->ants - i) / i < (head->length - len))
			break ;
		tmp->next = lm_antnew(lem, ++i, head->path_head);
		tmp = tmp->next;
		len = head->length;
	}
	return (i);
}

void	lm_march(t_lem *lem)
{
	VAR(int, ants, 0);
	VAR(int, done, 0);
	lm_print_paths(lem);
	if (lem->min_length == 1)
		lm_onestep(lem);
	else
	{
		VAR(t_ant*, leader, NULL);
		ants = list_init(lem, &leader);
		while (done < lem->ants)
		{
			lm_antprint(lem, leader);
			done += lm_ant_advance(lem, &leader);
			if (ants < lem->ants)
				ants = lm_antcat(lem, leader, ants);
		}
	}
	if (!lem->raw)
		ft_printf(GREEN"\nTurns: %d\n"RESET, lem->turn_count);
}
