/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 13:10:49 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/13 18:17:55 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

int	prube_scheduler(t_data *data, t_coder *this_coder, t_coder *coder)
{
	long long	mine;
	long long	other;

	if (data -> scheduler == FIFO)
	{
		mine = this_coder -> wait_start;
		other = coder -> wait_start;
	}
	else
	{
		mine = this_coder -> last_compile_start + data -> time_to_burnout;
		other = coder -> last_compile_start + data -> time_to_burnout;
	}
	if (other < mine
		|| (other == mine && this_coder -> coder_id < coder -> coder_id))
		return (0);
	return (1);
}

int	priority(t_coder *this_coder, t_table *table)
{
	int			n;
	int			i;
	t_data		*data;

	data = this_coder -> data;
	n = this_coder -> data -> num_coders;
	i = this_coder -> coder_id;
	if (!verif_priority(this_coder, data, table -> coders[(i + n - 1) % n]))
		return (0);
	if (!verif_priority(this_coder, data, table -> coders[(i + 1) % n]))
		return (0);
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
			table -> coders[i]-> wait_start = get_time();
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
