/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:52:40 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/06 13:02:09 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "coders.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long long time, coder **coder)
{
	usleep(time);
}

int	verif_time(long long data_time)
{
	long long	time;

	time = get_time();
	if (time < data_time)
		return (0);
	return (1);
}
