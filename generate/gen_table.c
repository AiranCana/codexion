/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 10:52:46 by acanadil          #+#    #+#             */
/*   Updated: 2026/07/06 15:55:57 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"
#include "../utils/utils.h"
#include "generate.h"

t_table	*gen_table(void)
{
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	if (pthread_mutex_init(&table -> mutex, NULL) != 0)
	{
		free(table);
		return (NULL);
	}
	if (pthread_cond_init(&table -> cond, NULL) != 0)
	{
		pthread_mutex_destroy(&table -> mutex);
		free(table);
		return (NULL);
	}
	return (table);
}

void	delete_table(t_table *table)
{
	if (table -> coders)
		delet_coders(table -> coders);
	pthread_cond_destroy(&table -> cond);
	pthread_mutex_destroy(&table -> mutex);
	free(table);
	table = NULL;
}
