/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_room_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 23:02:27 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/23 22:31:05 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	lm_size_r(t_room **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			++i;
	}
	return (i);
}

t_room	**lm_dupn_r(t_room **arr, int size)
{
	t_room	**dup;
	int		i;

	i = -1;
	if (!(dup = ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	if (arr)
	{
		while (arr[++i] && i < size)
			dup[i] = arr[i];
	}
	while (++i <= size)
		dup[i] = NULL;
	lm_del_r(arr);
	return (dup);
}

void	lm_print_r(t_room **arr)
{
	VAR(int, i, -1);
	if (arr)
	{
		while (arr[++i])
			ft_printf("	%s\n", arr[i]->name);
	}
}

void	lm_del_r(t_room **arr)
{
	if (arr)
		free(arr);
}
