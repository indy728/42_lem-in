/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 21:12:46 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/14 21:15:11 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lm_print_paths(t_lem *lem)
{
	if (lem->raw)
		return ;
	VAR(t_head*, path, lem->path_list);
	VAR(t_queue*, node, NULL);
	ft_printf(RED"%d"RESET" path%s found:\n\n", lem->path_count,
			lem->path_count > 1 ? "s" : "");
	while (path)
	{
		node = path->path_head;
		ft_printf(GREEN"%s"RESET"->", node->room->name);
		node = node->next;
		while (node->room != lem->end)
		{
			ft_printf("%s->", node->room->name);
			node = node->next;
		}
		ft_printf(RED"%s\n"RESET, node->room->name);
		path = path->next;
	}
	ft_putendl("");
}

void	lm_printerr(t_lem *lem, t_farm *head)
{
	if (!lem->raw && head)
	{
		VAR(t_farm*, print, head);
		while (print->next && print->next != head->prev)
		{
			print = print->next;
			ft_putendl(print->inst);
		}
		if (print->next)
			print = print->next;
		if (lem->marker < 3)
			ft_printf(RED"%s"YELLOW"$ <- invalid: %s\n"RESET,
					print->inst, lem->errstr);
		else
			ft_printf("%s\n"YELLOW"%s\n"RESET, print->inst, lem->errstr);
	}
	ft_printf("ERROR\n");
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
