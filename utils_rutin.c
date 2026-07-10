/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:32:54 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/10 14:44:34 by acanadil         ###   ########.fr       */
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
