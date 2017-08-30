/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_march.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 01:02:05 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/29 16:17:20 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lm_antcat(t_ant **head, t_ant *new)
{	
	if (*head && new)
	{
		VAR(t_ant*, tmp, *head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
}

t_ant	*lm_antnew(t_lem *lem, int i)
{
	VAR(t_ant*, new, (t_ant *)ft_memalloc(sizeof(t_ant)));
	VAR(char*, num, ft_itoa(i));
	new->name = ft_strjoin("L", num);
	new->current = lem->path;
	ft_strdel(&num);
	return (new);
}

void	lm_antdel(t_ant **head)
{
	VAR(t_ant*, tmp, *head);
	*head = (*head)->next;
	ft_strdel(&tmp->name);
	free(tmp);
}

int		lm_ant_advance(t_lem *lem, t_ant **head)
{
	VAR(t_ant*, tmp, *head);
	VAR(int, ret, 0);
	VAR(t_room*, del, (*head)->current->content);
	if (!ft_strcmp(del->name, lem->end->name))
	{
		lm_antdel(head);
		ret = 1;
	}
	while (tmp)
	{
		tmp->current = tmp->current->next;
		tmp = tmp->next;
	}
	return (ret);
}

void	lm_antprint(t_ant *head)
{
	VAR(t_room*, tmp, NULL);
	while (head)
	{
		tmp = head->current->content;
		ft_printf("%s-%s%s", head->name, tmp->name, head->next ? " " : "\n");
		head = head->next;
	}
}

void	lm_march(t_lem *lem)
{
	VAR(int, ant, 1);
	VAR(int, done, 0);
	VAR(t_ant*, head, lm_antnew(lem, 1));
	while (done < lem->ants)
	{
		done += lm_ant_advance(lem, &head);
		lm_antprint(head);
		if (++ant <= lem->ants)
			lm_antcat(&head, lm_antnew(lem, ant));
	}
}
