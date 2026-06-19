/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:56:26 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 16:02:33 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;
	char	*des;
	char	*sr;

	if (!dest && !src)
		return (dest);
	sr = (char *) src;
	des = dest;
	count = 0;
	while (count != n)
	{
		des[count] = sr[count];
		++count;
	}
	return (dest);
}
