/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:48:08 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:26:45 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s)
{
	void	*alloc;
	char	*dest;
	size_t	len;

	len = ft_strlen(s) + 1;
	alloc = malloc(sizeof (char) * len);
	if (!alloc)
		return (NULL);
	dest = alloc;
	while (*s)
	{
		*dest = *s;
		++dest;
		++s;
	}
	*dest = *s;
	return (alloc);
}
