/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 20:09:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/23 21:58:20 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_ants(t_lem *lem)
{
	char	*line;

	VAR(int, err, 0);
	while (lem->marker == 0 && get_next_line(0, &line) > 0)
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			++err;
		if (line[0] != '#')
		{
			if (!ft_isdigitstr(line) || 
					(lem->ants = ft_atoi(line)) <= 0)
				++err;
			++lem->marker;
		}
		ft_strdel(&line);
	}
	return (err);
}

int		get_links(t_lem *lem, char *line)
{
	char	*trim;
	char	**link;

	VAR(int, err, 0);
	++lem->marker;
	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		++err;
	if (line[0] != '#')
	{
		if (ft_strcmp(line, (trim = ft_strtrim2(line, '-'))))
			++err;
		else
		{
			link = ft_strsplit(line, '-');
			if (ft_size_r(link) != 2 || link[0][0] == 'L' ||
					link[1][0] == 'L')
				++err;
			else
			{
				if (!add_link(lem, link))
					++err;
			}
			ft_del_r(link);
		}
		ft_strdel(&trim);
	}
	ft_strdel(&line);
	while (!err && get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			++err;
		if (line[0] != '#')
		{
			if (ft_strcmp(line, (trim = ft_strtrim2(line, '-'))))
				++err;
			else
			{
				link = ft_strsplit(line, '-');
				if (ft_size_r(link) != 2 || link[0][0] == 'L' ||
						link[1][0] == 'L')
					++err;
				else
				{
					if (!add_link(lem, link))
						++err;
				}
				ft_del_r(link);
			}
			ft_strdel(&trim);
		}
		//ft_strdel(&line);
	}
	return (err);
}

int		get_rooms(t_lem *lem)
{
	char	*line;
	char	*trim;
	char	**room;

	VAR(int, err, 0);
	while (!err && lem->marker == 1 && get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (!ft_strcmp(line, "##start"))
			lem->start_next = 1;
		else if (!ft_strcmp(line, "##end"))
			lem->end_next = 1;
		if ((lem->start_next && lem->end_next) || !line[0] || line[0] == 'L')
			++err;
		if (line[0] != '#')
		{
			if (ft_strcmp(line, (trim = ft_strtrim2(line, ' '))))
				++err;
			else
			{
				room = ft_strsplit(line, ' ');
				if (ft_size_r(room) != 3)
					err += get_links(lem, line);
				else if (ft_size_r(room) == 3 && (!ft_isdigitstr(room[1]) ||
							!ft_isdigitstr(room[2])))
					++err;
				else
					add_room(lem, room);
				ft_del_r(room);
			}
			ft_strdel(&trim);
		}
	//	ft_strdel(&line);
	}
	return (err);
}


int		validate_instructions(t_lem *lem)
{
	VAR(int, err, 0);

	err += get_ants(lem);
	err += get_rooms(lem);
//	err += check_start_and_end(lem);
	return (err);
}

int main(int ac, char **av)
{
	char	*line;
	t_lem	*lem;

	lem = (t_lem *)ft_memalloc(sizeof(t_lem));
	lem->name_head = NULL;
	lem->coord_head = NULL;
	if (validate_instructions(lem))
	{
		ft_printf("invalid!\n");
	}
/*	ft_printf(GREEN"NAMES\n"RESET);
	lm_print_ntree(lem->name_head);
	ft_printf(RED"COORDS\n"RESET);
	lm_print_ctree(lem->coord_head);
*/	lm_bfs(lem);
	return (0);
}
