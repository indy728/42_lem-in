/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupn_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:07:20 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/22 22:47:40 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dupn_r(char **arr, int size)
{
	char	**dup;
	int		i;

	i = -1;
	if (!(dup = ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	if (arr)
	{
		while (arr[++i] && i < size)
			dup[i] = ft_strdup(arr[i]);
	}
	while (++i <= size)
		dup[i] = NULL;
	return (dup);
}
