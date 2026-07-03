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

#include "coders.h"
#include "generate/generate.h"
#include <errno.h>

int	verif_bornout(long long born, t_coder *coder)
{
	if (!verif_time(born + coder -> data -> time_to_burnout))
		return (1);
	coder -> state = BURNED_OUT;
	return (0);
}

void	print_coder(t_coder *coder)
{
	long long	time;
	char		*leter;

	leter = NULL;
	time = get_time();
	if (coder -> state == IDLE)
		leter = " has taken a dongle\n";
	else if (coder -> state == COMPILING)
		leter = " is compiling\n";
	else if (coder -> state == DEBUGGING)
		leter = " is debugging\n";
	else if (coder -> state == REFACTORING)
		leter = " is refactoring\n";
	else if (coder -> state == BURNED_OUT)
		leter = " has burned out\n";
	if (leter)
		printf(
			"%lli %i %s",
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
	pthread_mutex_lock(&coder -> right_usb -> mutex);
	coder -> right_usb -> cooldown_start = get_time();
	coder -> right_usb -> fre = 1;
	pthread_mutex_unlock(&coder -> right_usb -> mutex);
	pthread_mutex_lock(&coder -> left_usb -> mutex);
	coder -> left_usb -> cooldown_start = get_time();
	coder -> left_usb -> fre = 1;
	pthread_mutex_unlock(&coder -> left_usb -> mutex);
	coder -> compile_count++;
	coder -> last_compile_start = get_time();
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

static int	verif_usb_and_bornout(long long born, t_coder *coder)
{
	long long		time;
	struct timespec	ts;
	int				ret;

	time = born + coder -> data -> dongle_cooldown;
	ts.tv_sec = time / 1000;
	ts.tv_nsec = (time % 1000) * 1000;
	pthread_mutex_lock(&coder -> table -> mutex);
	while (!coder -> left_usb -> fre || !coder -> right_usb -> fre
		|| !priority(coder, coder -> table))
	{
		ret = pthread_cond_timedwait(
			&coder -> table -> cond,
			&coder -> table -> mutex, &ts);
		if (ret == ETIMEDOUT)
		{
			coder -> state = BURNED_OUT;
			pthread_mutex_unlock(&coder -> table -> mutex);
			return (0);
		}
	}
	takeusb(coder);
	coder -> state = COMPILING;
	pthread_mutex_unlock(&coder -> table -> mutex);
	return (1);
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
		if (verif_usb_and_bornout(born, coder))
			operate_pthread(coder, &born);
	}
	print_coder(coder);
}
