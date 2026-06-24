/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_pthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:48:56 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/24 16:02:57 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coders.h>

static int	takeusb(t_USB *usb, long long cooldown)
{
	if (usb -> fre)
	{
		usb -> fre = 0;
		if (verif_bornout(usb -> cooldown_start + cooldown))
			return (1);
		else
			usb -> fre = 1;
	}
	return (0);
}

static int	verif_bornout(long long born, t_coder *coder)
{
	if (!verif_time(born + coder -> data -> time_to_burnout))
		return (1);
	coder -> state = BURNED_OUT;
	return (0);
}

static void	print_coder(t_coder *coder)
{
	long long	time;
	char		*leter;

	leter = NULL;
	time = get_time();
	if (leter)
		printf(
			"%i %i %s",
			time - coder -> first_compile_start,
			coder -> coder_id,
			leter);
}

static void	operate_pthread(t_coder *coder, long long *born)
{
	coder -> state = COMPILING;
	*born = get_time();
	print_coder(coder);
	ft_sleep(coder -> data -> time_to_compile);
	coder -> right_usb -> cooldown_start = get_time();
	coder -> right_usb -> fre = 1;
	coder -> left_usb -> cooldown_start = get_time();
	coder -> left_usb -> fre = 1;
	coder -> compile_count++;
	coder -> state = DEBUGGING;
	print_coder(coder);
	ft_sleep(coder -> data -> time_to_debug);
	coder -> state = REFACTORING;
	print_coder(coder);
	ft_sleep(coder -> data -> time_to_refactor);
	if (coder -> compile_count == coder -> data -> number_of_compiles_required)
		coder -> state = FINISH;
	else
		coder -> state = IDLE;
}

void	ruotine(void *arg)
{
	t_coder		*coder;
	long long	born;

	coder = (t_coder *)arg;
	born = get_time();
	coder -> first_compile_start = get_time();
	coder -> last_compile_start = born;
	while (coder -> state != FINISH && coder -> state != BURNED_OUT)
	{
		if (takeusb(coder -> left_usb)
			&& verif_bornout(born, coder)
		)
		{
			if (takeusb(coder -> right_usb))
				operate_pthread(coder, &born);
			else
				coder -> left_usb -> fre = 1;
		}
	}
	print_coder(coder);
	return (NULL);
}
