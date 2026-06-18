/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:29:30 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:27:50 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*leter;
	size_t	count;

	count = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	leter = malloc(sizeof (char) * (len + 1));
	if (!leter)
		return (NULL);
	s += start;
	while (count < len)
	{
		leter[count] = s[count];
		count++;
	}
	leter[count] = '\0';
	return (leter);
}
