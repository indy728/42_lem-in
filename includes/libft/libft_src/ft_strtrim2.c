/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 19:40:20 by kmurray           #+#    #+#             */
/*   Updated: 2017/08/22 20:16:01 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_n(char *str, char c)
{
	VAR(int, i, -1);
	VAR(int, j, -1);
	VAR(int, n, 0);
	while (str[++j])
		;
	while (str[--j] == c && j >= 0)
		;
	while (str[++i] == c && i < j)
		;
	while (i < j + 1)
	{
		if (str[i] == c && str[i + 1] == c)
			;
		else
			++n;
		++i;
	}
	return (n);
}

char		*ft_strtrim2(char *str, char c)
{
	char	*trim;

	VAR(int, i, -1);
	VAR(int, j, -1);
	VAR(int, n, get_n(str, c));
	trim = ft_strnew(n + 1);
	while (str[++i] == c)
		;
	while (j < n)
	{
		if (str[i] == c && str[i + 1] == c)
			;
		else
			trim[++j] = str[i];
		++i;
	}
	trim[n] = 0;
	return (trim);
}
