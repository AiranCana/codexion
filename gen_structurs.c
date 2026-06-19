/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_structurs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:26:13 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:54:21 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "utils/utils.h"
#include <stdlib.h>
#include <string.h>

t_coder	*gen_coder(int coder_id, t_data *data)
{
	t_coder	*coder;

	coder = malloc(sizeof (t_coder));
	if (!coder)
		return (NULL);
	coder -> data = data;
	coder -> state = IDLE;
	coder -> coder_id = coder_id;
	coder -> last_compile_start = 0;
	coder -> thread_id = 0;
	return (coder);
}

static void	delet_coder(t_coder *coder)
{
	if (coder)
	{
		if (coder -> data)
			free(coder -> data);
		free(coder);
	}
}

void	*delet_coders(t_coder **coder)
{
	int	i;

	i = 0;
	while (coder[i])
	{
		delet_coder(coder[i]);
		i++;
	}
	free(coder);
	return (NULL);
}

t_data	*init_data(int argc, char **args)
{
	t_data	*data;

	if (argc != 8)
		return (NULL);
	data = malloc(sizeof (t_data));
	if (!data)
		return (NULL);
	data->time_to_burnout = ft_atol(args[1]);
	data->time_to_compile = ft_atol(args[2]);
	data->time_to_debug = ft_atol(args[3]);
	data->time_to_refactor = ft_atol(args[4]);
	data->number_of_compiles_required = ft_atoi(args[5]);
	data->dongle_cooldown = ft_atol(args[6]);
	if (strcmp(args[7], "fifo") == 0)
		data->scheduler = FIFO;
	else
		data->scheduler = EDF;
	return (data);
}
