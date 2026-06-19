/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:30:40 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:26:14 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	isfound(char s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		++set;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*allo;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (isfound(s1[start], set))
		++start;
	end = ft_strlen(s1) - 1;
	if (start >= end)
		return (ft_strdup(""));
	while (isfound(s1[end], set))
		--end;
	allo = ft_substr(s1, start, end - start + 1);
	return (allo);
}
