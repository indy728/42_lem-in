/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_mark_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:49:23 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/18 16:59:38 by kmurray          ###   ########.fr       */
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
		err = (str && str[0] == '-') ? 0 : 1;
		j = 0;
		while (!err && str[++j])
		{
			err = (str[j] == 'r' || str[j] == 'c' || str[j] == '1') ? 0 : 1;
			lem->raw = str[j] == 'r' ? 1 : lem->raw;
			lem->no_coords = str[j] == 'c' ? 1 : lem->no_coords;
			lem->one_path = str[j] == '1' ? 1 : lem->one_path;
		}
		if (err)
		{
			ft_putendl(USAGE);
			free(lem);
			exit(0);
		}
	}
}
