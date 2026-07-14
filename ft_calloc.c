/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:48:06 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/14 11:02:19 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allo;

	if (!nmemb || !size)
	{
		return (malloc(0));
	}
	allo = malloc(nmemb * size);
	if (!allo)
		return (NULL);
	ft_bzero(allo, size * nmemb);
	return (allo);
}
