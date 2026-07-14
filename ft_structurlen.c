/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structurlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:26:25 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/14 11:02:40 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/utils.h"

size_t	ft_structurlen(const void **s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
