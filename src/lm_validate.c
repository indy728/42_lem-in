/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:18:49 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/13 21:57:51 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				lm_get_ants(t_lem *lem)
{
	VAR(char*, line, NULL);
	VAR(int, err, 0);
	while (!err && lem->marker == 0 && get_next_line(0, &line) > 0)
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			err += lm_err_str(lem, ERR1);
		else if (line[0] != '#')
		{
			if (!ft_isdigitstr(line) ||
					(lem->ants = ft_atoi(line)) <= 0)
				err += lm_err_str(lem, ERR2);
			++lem->marker;
		}
		lm_farmadd(&lem->farm_head, lm_farmnew(line));
		ft_strdel(&line);
	}
	if (!err && !lem->ants)
		err += lm_err_str(lem, ERR2);
	return (err);
}

static void		validate_links(t_lem *lem, char *line, int *err)
{
	VAR(char*, trim, NULL);
	VAR(char**, link, NULL);
	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		*err += lm_err_str(lem, ERR3);
	else if (line[0] != '#')
	{
		if (ft_strcmp(line, (trim = ft_strtrim2(line, '-'))))
			*err += lm_err_str(lem, ERR4);
		else
		{
			link = ft_strsplit(line, '-');
			if (ft_size_r(link) != 2 || link[0][0] == 'L' ||
					link[1][0] == 'L')
				*err += lm_err_str(lem, ERR4);
			else
			{
				if (!add_link(lem, link))
					*err += lm_err_str(lem, ERR6);
			}
			ft_del_r(link);
		}
		ft_strdel(&trim);
	}
	lm_farmadd(&lem->farm_head, lm_farmnew(line));
	ft_strdel(&line);
}

static int		lm_get_links(t_lem *lem, char *line)
{
	VAR(int, err, 0);
	++lem->marker;
	if (lem->start_next || lem->end_next || !lem->start || !lem->end)
		err += lm_err_str(lem, "doodoo");
	validate_links(lem, line, &err);
	while (!err && get_next_line(0, &line) > 0)
		validate_links(lem, line, &err);
	return (err);
}

static void		validate_rooms(t_lem *lem, char *line, char **room, int *err)
{
	VAR(char*, trim, NULL);
	if (ft_strcmp(line, (trim = ft_strtrim2(line, ' '))))
		*err += lm_err_str(lem, ERR8);
	else
	{
		room = ft_strsplit(line, ' ');
		if (ft_size_r(room) != 3)
			*err += lm_get_links(lem, line);
		else if (ft_strchr(room[0], '-'))
			*err += lm_err_str(lem, ERR7);
		else if (ft_size_r(room) == 3 && (!ft_isdigitstr(room[1]) ||
					!ft_isdigitstr(room[2])))
			*err += lm_err_str(lem, ERR8);
		else
			add_room(lem, room);
		ft_del_r(room);
	}
	ft_strdel(&trim);
}

int				lm_get_rooms(t_lem *lem)
{
	VAR(char*, line, NULL);
	VAR(char**, room, NULL);
	VAR(int, err, 0);
	while (!err && lem->marker == 1 && get_next_line(0, &line) > 0)
	{
		if (!ft_strcmp(line, "##start"))
			lem->start_next = 1;
		else if (!ft_strcmp(line, "##end"))
			lem->end_next = 1;
		if ((lem->start_next && lem->end_next) || !line[0] || line[0] == 'L')
			err += lm_err_str(lem, ERR7);
		if (line[0] != '#')
			validate_rooms(lem, line, room, &err);
		if (lem->marker < 2)
			lm_farmadd(&lem->farm_head, lm_farmnew(line));
		if (lem->marker == 1)
			ft_strdel(&line);
	}
	if (!err)
		err += lem->marker == 2 ? 0 : lm_err_str(lem, "no links");
	return (err);
}
