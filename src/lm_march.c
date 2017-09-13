/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_march.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 01:02:05 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/12 18:24:23 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*lm_antnew(t_lem *lem, int i, t_queue *path)
{
	VAR(t_ant*, new, (t_ant *)ft_memalloc(sizeof(t_ant)));
	VAR(char*, num, ft_itoa(i));
	new->name = ft_strjoin("L", num);
	new->current = path;
	ft_strdel(&num);
	return (new);
}

int		lm_antcat(t_lem *lem, t_ant *leader, int ants)
{	
	VAR(int, i, -1);
	VAR(t_ant*, tmp, leader);
	VAR(t_list*, path, lem->path_list);
	while (tmp->next)
		tmp = tmp->next;
	while (path && ants < lem->ants && ++i < lem->path_count)
	{	
		tmp->next = lm_antnew(lem, ++ants, ((t_head *)(path->content))->path_head);
		path = path->next;
		tmp = tmp->next;
	}
	return (ants);
}

void	lm_antdel(t_ant **leader)
{
	VAR(t_ant*, tmp, *leader);
	if (*leader/* == line*/)
		*leader = (*leader)->next;
/*	else
	{
		while (tmp->next && tmp->next != line)
			tmp = tmp->next;
		tmp->next = line->next;
		tmp = line;
	}*/
	ft_strdel(&tmp->name);
	free(tmp);
}

/*int		lm_ant_advance(t_lem *lem, t_ant **path)
{
	VAR(t_ant*, tmp, NULL);
	VAR(int, ret, 0);
	VAR(t_room*, del, NULL);
	VAR(int, i, -1);
	while (++i < lem->path_count)
	{
		tmp = path[i];
		if (path[i])
			del = path[i]->current->content;
		if (!ft_strcmp(del->name, lem->end->name))
		{
			lm_antdel(path, i);
			++ret;
		}
		while (tmp)
		{
			tmp->current = tmp->current->next;
			tmp = tmp->next;
		}
	}
	return (ret);
}*/

int		lm_ant_advance(t_lem *lem, t_ant **leader)
{
	VAR(t_ant*, line, *leader);
	VAR(int, ret, 0);
	VAR(t_room*, del, NULL);
	VAR(int, i, -1);
	while (line)
	{
		del = line->current->room;
		line->current = line->current->next;
		line = line->next;
		if (!ft_strcmp(del->name, lem->end->name))
		{
			lm_antdel(leader);
			++ret;
		}
	/*	if (line)
		{
		//	if (ret)
		//		ft_printf(GREEN" line: %p line->name: %s line->current %p"RESET, line, line->name, line->current);
		}*/
	}
	return (ret);
}

/*void	lm_antprint(t_lem *lem, t_ant **paths)
{
	VAR(t_room*, tmp, NULL);
	VAR(t_ant*, line, NULL);
	VAR(int, i, -1);
	while (++i < lem->path_count)
	{
		line = paths[i];
		while (line)
		{
			tmp = line->current->content;
			ft_printf("%s-%s%s", line->name, tmp->name,
					line->next || paths[i + 1] ? " " : "\n");
			line = line->next;
		}
	}
}*/

void	lm_antprint(t_lem *lem, t_ant *leader)
{
	VAR(t_room*, tmp, NULL);
	VAR(t_ant*, line, leader);
	VAR(int, i, 0);
	while (line)
	{
		tmp = line->current->room;
		ft_printf("%s-%s%s", line->name, tmp->name,
				line->next || ++i < lem->path_count ? " " : "\n");
		line = line->next;
	}
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
}

void	lm_initpaths(t_lem *lem, t_ant **paths)
{
	VAR(int, i, 0);
	VAR(t_list*, node, lem->path_list);
	while (i < lem->path_count)
	{
		paths[i] = lm_antnew(lem, i + 1, ((t_head *)(node->content))->path_head);
		node = node->next;
		++i;
	}
}

/*void	lm_march(t_lem *lem)
{
	VAR(int, ant, lem->path_count);
	VAR(int, done, 0);
	if (lem->min_length == 1)
		lm_onestep(lem);
	else
	{
		VAR(t_ant**, paths, (t_ant **)ft_memalloc(sizeof(t_ant *) * (lem->path_count + 1)));
		lm_initpaths(lem, paths);
		while (done < lem->ants)
		{
			done += lm_ant_advance(lem, paths);
			lm_antprint(lem, paths);
			if (ant <= lem->ants)
				ant = lm_antcat(lem, paths, ant);
			//ft_printf(RED"done: %d\n"RESET, done);
		}
	}
}*/

int		list_init(t_lem *lem, t_ant **leader)
{	
	VAR(int, i, 0);
	VAR(t_list*, path, lem->path_list);
	VAR(t_head*, head, (t_head *)(path->content));
	*leader = lm_antnew(lem, ++i, head->path_head);
	VAR(t_ant*, tmp, *leader);
	while (path && i < lem->ants && i < lem->path_count)
	{	
		path = path->next;
		head = (t_head *)path->content;
		tmp->next = lm_antnew(lem, ++i, head->path_head);
		tmp = tmp->next;
	}
	return (i);
}

void	lm_march(t_lem *lem)
{
	VAR(int, ants, 0);
	VAR(int, done, 0);
	if (lem->min_length == 1)
		lm_onestep(lem);
	else
	{
		VAR(t_ant*, leader, (t_ant *)ft_memalloc(sizeof(t_ant)));
		ants = list_init(lem, &leader);
		while (done < lem->ants)
		{
			done += lm_ant_advance(lem, &leader);
			lm_antprint(lem, leader);
			if (ants < lem->ants)
				ants = lm_antcat(lem, leader, ants);
			ft_printf(RED"done: %d\n"RESET, done);
		}
	}
}
