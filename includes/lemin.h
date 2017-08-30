/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:59:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/29 15:29:18 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define ERR1 "start/end command before ant count"
# define ERR2 "first instruction must be ant count > 0"
# define ERR3 "start/end command precedes link instruction"
# define ERR4 "poor link instruction formatting"
# define ERR5 ""
# define ERR6 "link room name does not exist"
# define ERR7 "invalid room name"////////// multiple error possibilities
# define ERR8 "poor room instruction formatting"
# define ERR9 ""

# define INROOM current->room->name

# define KMDB(x) ft_printf("%s\n", x)

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

typedef struct		s_ant
{
	char			*name;
	t_list			*current;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_farm
{
	char			*inst;
	struct s_farm	*next;
	struct s_farm	*prev;
}					t_farm;

typedef struct		s_lem
{
	unsigned int	ants;
	char			*errstr;
	t_bool			start_next;
	t_bool			end_next;
	int				marker;
	t_list			*path;	
	t_room			*start;
	t_room			*end;
	t_farm			*farm_head;
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

t_farm				*lm_farmnew(char *str);
void				lm_farmadd(t_farm **head, t_farm *new);
void				lm_farmdel(t_farm **head);
void				lm_printfarm(t_farm *head);
void				lm_printerr(t_lem *lem, t_farm *head);
void				lm_march(t_lem *lem);

#endif
