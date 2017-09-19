/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 20:09:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/18 18:28:16 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lm_err_str(t_lem *lem, char *str)
{
	lem->errstr = ft_strdup(str);
	return (1);
}

int		validate_instructions(t_lem *lem)
{
	VAR(int, err, 0);
	if (!(err += lm_get_ants(lem)))
		err += lm_get_rooms(lem);
	if (!err)
		++lem->marker;
	if (!err && (!lem->start->links || !lem->end->links))
		err += lm_err_str(lem, ERR9);
	return (err);
}

void	set_max_paths(t_lem *lem)
{
	VAR(int, start, 1);
	VAR(int, end, 1);
	VAR(t_queue*, tmp, lem->start->links);
	if (lem->one_path)
	{
		lem->max_paths = 1;
		return ;
	}
	while ((tmp = tmp->next))
		++start;
	tmp = lem->end->links;
	while ((tmp = tmp->next))
		++end;
	lem->max_paths = ft_min(start, end);
	lem->max_paths = ft_min(lem->max_paths, lem->ants);
}

int		main(int ac, char **av)
{
	VAR(char*, line, NULL);
	VAR(char*, error, NULL);
	VAR(t_lem*, lem, (t_lem *)ft_memalloc(sizeof(t_lem)));
	if (!lem)
	{
		ft_printf("memory allocation failed: size of: struct s_lem\n");
		exit(0);
	}
	if (ac > 1)
		lm_mark_options(ac, av, lem);
	if (validate_instructions(lem))
		lm_printerr(lem, lem->farm_head);
	else
	{
		set_max_paths(lem);
		lm_printfarm(lem->farm_head);
		if (lm_bfs(lem))
			lm_march(lem);
		else
			lm_printerr(lem, lem->farm_head);
	}
	lm_delete(lem);
	return (0);
}
