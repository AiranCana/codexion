/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsUsb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:19:24 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/13 11:54:17 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	asign_usb(t_USB **usb, t_coder **coders)
{
	size_t	len;
	int		i;

	len = ft_structurlen((const void **)coders);
	i = 0;
	while (usb[i])
	{
		coders[i]-> right_usb = usb[(i + 1) % len];
		coders[i]-> left_usb = usb[i];
		i++;
	}
}

void	takeusb(t_coder **coder)
{
	pthread_mutex_lock(&(*coder)-> right_usb -> mutex);
	(*coder)-> right_usb -> fre = 0;
	print_coder(*coder);
	pthread_mutex_unlock(&(*coder)-> right_usb -> mutex);
	pthread_mutex_lock(&(*coder)-> left_usb -> mutex);
	(*coder)-> left_usb -> fre = 0;
	print_coder(*coder);
	pthread_mutex_unlock(&(*coder)-> left_usb -> mutex);
	(*coder)-> state = COMPILING;
}

void	dropusb(t_coder **coder)
{
	pthread_mutex_lock(&(*coder)-> table -> mutex);
	(*coder)-> right_usb -> cooldown_start = get_time();
	(*coder)-> left_usb -> fre = 1;
	(*coder)-> left_usb -> cooldown_start = get_time();
	(*coder)-> right_usb -> fre = 1;
	pthread_cond_broadcast(&(*coder)-> table -> cond);
	pthread_mutex_unlock(&(*coder)-> table -> mutex);
}

int	available_usbs(t_coder *coder)
{
	long long	now;

	now = get_time();
	if (coder -> coder_id % 2)
	{
		if (!coder -> left_usb -> fre || now - coder
			-> left_usb -> cooldown_start < coder -> data -> dongle_cooldown)
			return (0);
		if (!coder -> right_usb -> fre || now - coder
			-> right_usb -> cooldown_start < coder -> data -> dongle_cooldown
			|| coder -> right_usb -> id == coder -> left_usb -> id)
			return (0);
	}
	else
	{
		if (!coder -> right_usb -> fre || now - coder
			-> right_usb -> cooldown_start < coder -> data -> dongle_cooldown)
			return (0);
		if (!coder -> left_usb -> fre || now - coder
			-> left_usb -> cooldown_start < coder -> data -> dongle_cooldown
			|| coder -> right_usb -> id == coder -> left_usb -> id)
			return (0);
	}
	return (1);
}

int	veif_priority(t_coder *this, t_data *data, t_coder *coder)
{
	if (coder->coder_id != this->coder_id && coder->state == IDLE
		&& available_usbs(coder))
	{
		if (!prube_scheduler(data, this, coder))
			return (0);
	}
	return (1);
}
