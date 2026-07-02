/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 13:10:49 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/24 13:11:36 by acanadil         ###   ########.fr       */
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
