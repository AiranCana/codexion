/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tructurlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:26:25 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/22 13:27:09 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_structurlen(const void **s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
