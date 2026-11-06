/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:52:40 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/06 13:24:49 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_sleep(long long time, t_coder **coder)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if ((*coder)-> table -> failed || (((*coder)-> state == BURNED_OUT
					&& verif_time((*coder)-> first_compile_start
						+ (*coder)-> data -> time_to_burnout))))
			return (0);
		usleep(500);
	}
	return (1);
}

int	verif_time(long long data_time)
{
	long long	time;

	time = get_time();
	if (time < data_time)
		return (0);
	return (1);
}

void	wait_time(t_coder *coder)
{
	struct timespec	ts;
	struct timeval	now;
	long long		total_ns;

	gettimeofday(&now, NULL);
	total_ns = (long long)now.tv_usec * 1000 + 1000000LL;
	ts.tv_sec = now.tv_sec + (total_ns / 1000000000LL);
	ts.tv_nsec = total_ns % 1000000000LL;
	pthread_cond_timedwait(
		&coder -> table -> cond,
		&coder -> table -> mutex,
		&ts);
}

void	asign_state(t_coder *coder, int state)
{
	pthread_mutex_lock(&coder -> table -> mutex);
	coder -> state = state;
	pthread_mutex_unlock(&coder -> table -> mutex);
}
