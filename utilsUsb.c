/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsUsb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:19:24 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/03 13:19:24 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "utils/utils.h"
#include "generate/generate.h"

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

void	takeusb(t_coder *coder)
{
	coder -> left_usb -> fre = 0;
	print_coder(coder);
	coder -> right_usb -> fre = 0;
	print_coder(coder);
}

void dropusb(t_coder *coder)
{
    coder -> left_usb -> fre = 1;
    print_coder(coder);
    coder -> right_usb -> fre = 1;
    print_coder(coder);
}