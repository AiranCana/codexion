/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:32:54 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/13 11:48:29 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

int	all_coders_finish(t_table *table)
{
	int	i;

	i = 0;
	while (table -> coders[i])
	{
		if (table -> coders[i]-> state != FINISH)
			return (0);
		i++;
	}
	return (1);
}

static int	operations_dead(t_table *table)
{
	table -> failed = 1;
	pthread_cond_broadcast(&table -> cond);
	return (1);
}


int	found_dead(t_table *table)
{
	int			i;
	long long	now;

	now = get_time();
	i = 0;
	while (table->coders[i])
	{
		if (table -> coders[i]-> state != FINISH
			&& table -> coders[i]-> state != BURNED_OUT
			&& now - table -> coders[i]-> last_compile_start
			> table -> coders[i]-> data -> time_to_burnout)
		{
			table -> coders[i]-> state = BURNED_OUT;
			print_coder(table -> coders[i]);
			return (operations_dead(table));
		}
		else if (table -> coders[i]-> state == BURNED_OUT)
			return (operations_dead(table));
		i++;
	}
	return (0);
}
