/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_pthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:48:56 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/14 12:14:49 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	print_coder(t_coder *coder)
{
	long long	time;
	char		*leter;

	leter = NULL;
	time = get_time();
	if (coder -> state == IDLE)
		leter = "has taken a dongle\n";
	else if (coder -> state == COMPILING)
		leter = "is compiling\n";
	else if (coder -> state == DEBUGGING)
		leter = "is debugging\n";
	else if (coder -> state == REFACTORING)
		leter = "is refactoring\n";
	else if (coder -> state == BURNED_OUT)
		leter = "has burned out\n";
	if (leter && verif_bornout(coder))
		printf(
			"%lli %i %s", time - coder -> first_compile_start,
			coder -> coder_id, leter);
}

static void	operate_pthread(t_coder *coder, long long *born)
{
	printer_coder(coder);
	*born = get_time();
	coder -> last_compile_start = *born;
	if (!ft_sleep(coder -> data -> time_to_compile, &coder))
	{
		dropusb(&coder);
		return ;
	}
	dropusb(&coder);
	coder -> compile_count++;
	coder -> state = DEBUGGING;
	printer_coder(coder);
	if (!ft_sleep(coder -> data -> time_to_debug, &coder))
		return ;
	coder -> state = REFACTORING;
	printer_coder(coder);
	if (!ft_sleep(coder -> data -> time_to_refactor, &coder))
		return ;
	if (coder -> compile_count == coder -> data -> number_of_compiles_required)
		coder -> state = FINISH;
	else
		coder -> state = IDLE;
}

static int	verif_usb_and_bornout(long long *born, t_coder *coder)
{
	long long		time;

	time = *born + coder -> data -> time_to_burnout;
	pthread_mutex_lock(&coder -> table -> mutex);
	while ((!available_usbs(coder) || !priority(coder, coder -> table))
		&& !coder -> table -> failed)
	{
		if (verif_time(time))
		{
			coder -> state = BURNED_OUT;
			pthread_cond_broadcast(&coder -> table -> cond);
			pthread_mutex_unlock(&coder -> table -> mutex);
			return (0);
		}
		wait_time(coder);
	}
	if (coder -> table -> failed)
	{
		pthread_mutex_unlock(&coder -> table -> mutex);
		return (0);
	}
	takeusb(&coder);
	*born = get_time();
	pthread_mutex_unlock(&coder -> table -> mutex);
	return (1);
}

void	*ruotine(void *arg)
{
	t_coder		*coder;
	long long	born;

	coder = (t_coder *)arg;
	born = get_time();
	coder -> first_compile_start = get_time();
	coder -> last_compile_start = born;
	while ((coder -> state != FINISH && coder -> state != BURNED_OUT))
	{
		pthread_mutex_lock(&coder -> table -> mutex);
		if (coder -> table -> failed)
		{
			pthread_mutex_unlock(&coder -> table -> mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&coder -> table -> mutex);
		if (verif_usb_and_bornout(&born, coder))
			operate_pthread(coder, &born);
	}
	if (coder -> state == BURNED_OUT && !coder -> bornout_log)
	{
		printer_coder(coder);
		coder -> bornout_log = 1;
	}
	return (NULL);
}

void	*rutine_table(void *arg)
{
	t_table	*table;
	int		i;
	int		found;

	found = 0;
	table = (t_table *)arg;
	while (!found)
	{
		pthread_mutex_lock(&table -> mutex);
		if (table -> failed)
			found = 1;
		else
			found = found_dead(table);
		if (all_coders_finish(table))
			found = 1;
		pthread_mutex_unlock(&table -> mutex);
		if (!found)
			usleep(500);
	}
	return (NULL);
}
