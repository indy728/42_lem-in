/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:59:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 14:54:52 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define USAGE "lem-in: usage: ./lem-in [-1rc] < path_to_file"

# define ERR1 "start/end command before ant count"
# define ERR2 "first instruction must valid digit string > 0 (integer)"
# define ERR3 "start/end command precedes link instruction"
# define ERR4 "poor link instruction formatting"
# define ERR5 "empty file"
# define ERR6 "link room name does not exist"
# define ERR7 "illegal room name"
# define ERR8 "poor room instruction formatting"
# define ERR9 "no possible paths"
# define ERR10 "link to self"
# define ERR11 "coordinate integer overflow"
# define ERR12 "improper start or end room formatting"
# define ERR13 "no links"
# define ERR14 "no start or end room"

# define KMDB(x) ft_printf("%s\n", x)

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				used;
	struct s_room	*prev;
	struct s_queue	*links;
	struct s_room	*nleft;
	struct s_room	*nright;
	struct s_room	*cleft;
	struct s_room	*cright;
}					t_room;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_ant
{
	char			*name;
	t_queue			*current;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_farm
{
	char			*inst;
	struct s_farm	*next;
	struct s_farm	*prev;
}					t_farm;

typedef struct		s_head
{
	t_queue			*path_head;
	int				length;
	struct s_head	*next;
}					t_head;

typedef struct		s_lem
{
	unsigned int	ants;
	unsigned int	max_paths;
	char			*errstr;
	t_bool			start_next;
	t_bool			end_next;
	int				marker;
	t_head			*path_list;
	int				path_count;
	int				min_length;
	int				turn_count;
	t_bool			dupe;
	t_bool			raw;
	t_bool			no_coords;
	t_bool			one_path;
	t_room			*start;
	t_room			*end;
	t_farm			*farm_head;
	t_room			*name_head;
	t_room			*coord_head;
}					t_lem;

void				lm_mark_options(int ac, char **av, t_lem *lem);
char				lm_bfs(t_lem *lem);
void				lm_delete(t_lem *lem);
void				lm_headcat(t_head **head, t_head *new);

/*
**	Adding rooms to farm and links to rooms (lm_add_attr.c).
*/

void				add_room(t_lem *lem, char **room);
int					add_link(t_lem *lem, char **link);
void				set_start_end(t_lem *lem, t_room *new);
void				lm_name_insert(t_lem *lem, t_room **head, t_room *new);
void				lm_coord_insert(t_lem *lem, t_room **head, t_room *new);
void				lm_destroy_tree(t_room *root);
void				lm_clear_ntree(t_room *room);

/*
**	Parsing and farm validation (lm_validate.c).
*/

int					lm_get_ants(t_lem *lem);
int					lm_get_rooms(t_lem *lem);

/*
**	Saving the farm to print on success (lm_farm.c).
*/

t_farm				*lm_farmnew(char *str);
void				lm_farmadd(t_farm **head, t_farm *new);
void				lm_farmdel(t_lem *lem);

/*
**	Print functions for output (lm_print.c).
*/

void				lm_printfarm(t_farm *head);
void				lm_printerr(t_lem *lem, t_farm *head);
void				lm_print_paths(t_lem *lem);
int					lm_err_str(t_lem *lem, char *str);

/*
**	Make ants, add ants, move ants kill ants (lm_march.c, lm_ants.c).
*/

t_ant				*lm_antnew(int i, t_queue *path);
unsigned int		lm_antcat(t_lem *lem, t_ant *leader, unsigned int ants);
void				lm_antdel(t_ant **leader, t_ant *del);
void				lm_march(t_lem *lem);

/*
**	Special list functions for rooms (lm_queue.c).
*/

t_queue				*lm_qnew(t_room *room);
void				lm_qadd(t_queue **head, t_queue *new);
void				lm_qcat(t_queue **head, t_queue *new);
void				lm_qdelhead(t_queue **head);
void				lm_qdel(t_queue **head);

#endif
