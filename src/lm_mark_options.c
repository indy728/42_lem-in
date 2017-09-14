/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_mark_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:49:23 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/13 23:10:15 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			lm_mark_options(int ac, char **av, t_lem *lem)
{
	VAR(char*, str, NULL);
	VAR(int, i, 0);
	VAR(int, j, 0);
	VAR(char, err, 0);
	while (++i < ac)
	{
		str = av[i];
		if (str && str[0] == '-' )
		{
			j = 0;
			while (!err && str[++j])
			{
				err = (str[j] == 'r' || str[j] == 'c') ? 0 : 1;
				lem->raw = str[j] == 'r' ? 1 : lem->raw;
				lem->no_coords = str[j] == 'r' ? 1 : lem->no_coords;
			}
		}
		else
			++err;
		if (err)
		{
			ft_putendl(USAGE);
			free(lem);
			exit(0);
		}
	}
}
