/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 10:52:46 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/23 12:12:00 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"
#include "../utils/utils.h"
#include "generate.h"

t_table	*gen_table(t_coder **coders)
{
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	table -> coders = coders;
	return (table);
}

void	delete_table(t_table *table)
{
	delet_coders(table -> coders);
	free(table);
	table = NULL;
}
