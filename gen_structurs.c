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
#include <stdlib.h>

t_coder	*gen_coder(int coder_id, t_data *data)
{
	t_coder	*coder;

	coder = malloc(sizeof (t_coder));
	if (!coder)
		return (NULL);
	coder -> data = data;
	coder -> live = 1;
	coder -> coder_id = coder_id;
	return (coder);
}

void	delet_coder(t_coder *coder)
{
	if (coder -> data)
		free(coder -> data);
	free(coder);
	coder = NULL;
}

t_data	*gen_data(void)
{
	t_data	*data;

	data = malloc(sizeof (t_coder));
	if (!data)
		return (NULL);
	return (data);
}
