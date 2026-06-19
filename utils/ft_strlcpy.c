/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:21:13 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:27:03 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*sol;
	char		*dest;
	size_t		count;

	count = 0;
	sol = src;
	dest = dst;
	if (size <= 0)
		return (ft_strlen(sol));
	while (*src && (size - 1) > count++)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return (ft_strlen(sol));
}
