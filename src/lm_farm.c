/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_farm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 23:40:28 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/29 00:19:44 by kmurray          ###   ########.fr       */
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

void	lm_farmdel(t_farm **head)
{
	if (*head)
	{
		VAR(t_farm*, del, *head);
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
		*head = NULL;
	}
}

void	lm_printerr(t_lem *lem, t_farm *head)
{
	if (head)
	{
		VAR(t_farm*, print, head);
		ft_putendl(print->inst);
		print = print->next;
		while (print && print != head->prev)
		{
			ft_putendl(print->inst);
			print = print->next;
		}
		ft_printf("%s$ "RED"<- invalid: %s\n"RESET, print->inst, lem->errstr);
	}
}

void	lm_printfarm(t_farm *head)
{
	if (head)
	{
		VAR(t_farm*, print, head);
		ft_putendl(print->inst);
		print = print->next;
		while (print && print != head)
		{
			ft_putendl(print->inst);
			print = print->next;
		}
		ft_putendl("");
	}
}
