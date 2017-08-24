/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:59:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/23 22:26:08 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define KMDB(x) ft_printf("%s\n", x);

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*prev;
	struct s_room	**links;
	struct s_room	*nleft;
	struct s_room	*nright;
	struct s_room	*cleft;
	struct s_room	*cright;
}					t_room;

typedef struct		s_path
{
	t_room			*room;
	struct s_path	*next;
}					t_path;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_lem
{
	unsigned int	ants;
	t_bool			start_next;
	t_bool			end_next;
	int				marker;
	t_list			*path;	
	t_room			*start;
	t_room			*end;
	t_room			*name_head;
	t_room			*coord_head;
}					t_lem;

void				add_room(t_lem *lem, char **room);
int					add_link(t_lem *lem, char **link);
int					lm_size_r(t_room **arr);
t_room				**lm_dupn_r(t_room **arr, int size);
void				lm_del_r(t_room **arr);
void				lm_print_r(t_room **arr);
void				lm_name_insert(t_lem *lem, t_room **head, t_room *new);
void				lm_coord_insert(t_lem *lem, t_room **head, t_room *new);
void				lm_destroy_tree(t_room *root);
void				lm_print_ntree(t_room *room);
void				lm_print_ctree(t_room *room);
t_list				*lm_bfs(t_lem *lem);

#endif
