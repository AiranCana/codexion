/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_usb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:12:11 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/14 11:03:07 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

static t_USB	*gen_usb(int num)
{
	t_USB	*usb;

	usb = ft_calloc(sizeof(t_USB), 1);
	if (!usb)
		return (NULL);
	if (pthread_mutex_init(&usb -> mutex, NULL) != 0)
	{
		free(usb);
		return (NULL);
	}
	usb -> id = num;
	usb -> fre = 1;
	return (usb);
}

void	*delet_usbs(t_USB **usb)
{
	int	i;

	i = 0;
	while (usb[i])
	{
		if (usb[i])
		{
			pthread_mutex_destroy(&usb[i]-> mutex);
			free(usb[i]);
			usb[i] = NULL;
		}
		i++;
	}
	free(usb);
	usb = NULL;
	return (NULL);
}

t_USB	**gen_usbs(size_t num)
{
	t_USB	**usb;
	int		i;

	i = 0;
	usb = ft_calloc(sizeof(t_USB *), num + 1);
	if (!usb)
		return (NULL);
	while (i < num)
	{
		usb[i] = gen_usb(i + 1);
		if (!usb[i] || pthread_mutex_init(&usb[i]-> mutex, NULL) != 0)
			return (delet_usbs(usb));
		i++;
	}
	return (usb);
}
