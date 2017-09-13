/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 23:10:20 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/06 00:28:20 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*lm_paths(t_lem *lem)
{
	VAR(t_list*, begin_list, NULL);
	while (lem->path_count + 1 <= lem->ants /*&& 
			lem->ants / (lem->path_count + 1) + lem->min_length > new_len*/)//add to lm_bfs
	{
		lem->min_length == 1)
			break ;
		
	}
	return (begin_list);
}
