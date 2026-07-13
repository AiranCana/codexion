/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 13:10:49 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/13 11:29:40 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static int	prube_scheduler(t_data *data, t_coder *this_coder, t_coder *coder)
{
	long long	born;
	long long	other_born;
	long long	this_born;

	born = data -> time_to_burnout;
	if (data -> scheduler == FIFO)
	{
		if (coder -> last_compile_start < this_coder -> last_compile_start)
			return (0);
	}
	else if (data -> scheduler == EDF)
	{
		this_born = this_coder -> last_compile_start + born;
		other_born = coder -> last_compile_start + born;
		if (other_born < this_born)
			return (0);
	}
	return (1);
}

int	priority(t_coder *this_coder, t_table *table)
{
	int		i;
	t_coder	*coder;
	t_data	*data;

	data = this_coder -> data;
	i = 0;
	while (table -> coders[i])
	{
		coder = table -> coders[i];
		if (coder->coder_id != this_coder->coder_id && coder->state == IDLE)
		{
			if (!prube_scheduler(data, this_coder, coder))
				return (0);
		}
		i++;
	}
	return (1);
}

void	wait_codex(t_table *table, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(table->coders[j]->thread_id, NULL);
		j++;
	}
}

static void	start_time(t_table *table)
{
	int	i;

	i = 0;
	while (table -> coders[i])
	{
		table -> coders[i]-> last_compile_start = get_time();
		i++;
	}
}

int	start_routin(t_table *table)
{
	int	i;

	i = 0;
	start_time(table);
	if (pthread_create(&table -> thread_id, NULL, &rutine_table, table) != 0)
		return (printer_error("in the creation of monitor"));
	while (table -> coders[i])
	{
		if (pthread_create(&table -> coders[i]-> thread_id, NULL,
				&ruotine, table ->coders[i]) != 0)
		{
			pthread_mutex_lock(&table -> mutex);
			table -> failed = 1;
			pthread_cond_broadcast(&table -> cond);
			pthread_mutex_unlock(&table -> mutex);
			wait_codex(table, i);
			pthread_join(table->thread_id, NULL);
			return (printer_error("in the creation of pthread"));
		}
		i++;
	}
	wait_codex(table, i);
	pthread_join(table->thread_id, NULL);
	return (1);
}
