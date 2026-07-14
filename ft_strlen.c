/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:35:43 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/14 11:02:32 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/utils.h"

size_t	ft_strlen(const char *line)
{
	size_t	len;

	len = 0;
	while (*(line++))
		++len;
	return (len);
}
