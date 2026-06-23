/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_usb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:12:11 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/23 12:58:48 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static t_USB	*gen_usb(int num)
{
	t_USB	*usb;

	usb = ft_calloc(sizeof(t_USB), 1);
	if (!usb)
		return (NULL);
	return (usb);
}

void	*delet_usbs(t_USB **usb)
{
	int	i;

	i = 0;
	while (usb[i])
	{
		free(usb[i]);
		usb[i] = NULL;
		i++;
	}
	free(usb);
	usb = NULL;
	return (NULL);
}

t_USB	**gen_usbs(size_t num)
{
	t_USB	**usb;
	int		i;

	i = 0;
	usb = ft_calloc(sizeof(t_USB *), num + 1);
	if (!usb)
		return (NULL);
	while (i < num)
	{
		usb[i] = gen_usb(i + 1);
		if (!usb[i])
			return (delet_usbs(usb));
		i++;
	}
	return (usb);
}

void	asign_usb(t_USB **usb, t_coder **coders)
{
	size_t	len;
	int		i;

	len = ft_structurlen((const void **)coders);
	i = 0;
	while (usb[i])
	{
		coders[i]-> right_usb = usb[(i + 1) % len];
		coders[i]-> left_usb = usb[i];
		i++;
	}
}

// static const char	*get_state_str(t_state state)
// {
// 	if (state == IDLE)
// 		return ("IDLE");
// 	if (state == FISNI)
// 		return ("FISNI");
// 	if (state == COMPILING)
// 		return ("COMPILING");
// 	if (state == DEBUGGING)
// 		return ("DEBUGGING");
// 	if (state == REFACTORING)
// 		return ("REFACTORING");
// 	return ("BURNED_OUT");
// }

// static void	print_data(t_data *data)
// {
// 	if (!data)
// 	{
// 		printf("Data: NULL\n");
// 		return ;
// 	}
// 	printf("=========================================\n");
// 	printf("           GLOBAL CONFIGURATION          \n");
// 	printf("=========================================\n");
// 	printf("Time to Burnout:    %lld ms\n", data->time_to_burnout);
// 	printf("Time to Compile:    %lld ms\n", data->time_to_compile);
// 	printf("Time to Debug:      %lld ms\n", data->time_to_debug);
// 	printf("Time to Refactor:   %lld ms\n", data->time_to_refactor);
// 	printf("Compiles Required:  %d\n", data->number_of_compiles_required);
// 	printf("Dongle Cooldown:    %lld ms\n", data->dongle_cooldown);
// 	printf("Scheduler Type:     %s\n", data->scheduler == FIFO ? "FIFO" : "EDF");
// 	printf("=========================================\n\n");
// }

// static void	print_coder(t_coder *coder)
// {
// 	if (!coder)
// 		return ;
// 	printf("--- Coder ID: %d ---\n", coder->coder_id);
// 	printf("  Thread ID:    %lu\n", (unsigned long)coder->thread_id);
// 	printf("  State:        %s\n", get_state_str(coder->state));
// 	printf("  Compiles:     %d/%d\n", coder->compile_count, coder->data ? coder->data->number_of_compiles_required : 0);
// 	printf("  Last Compile: %lld ms\n", coder->last_compile_start);

// 	if (coder->left_usb)
// 		printf("  Left USB ID:  %d\n", coder->left_usb->id);
// 	else
// 		printf("  Left USB:     NONE\n");

// 	if (coder->right_usb)
// 		printf("  Right USB ID: %d\n", coder->right_usb->id);
// 	else
// 		printf("  Right USB:    NONE\n");
// 	printf("\n");
// }

// void	print_all_coders(t_table *table)
// {
// 	int	i;
// 	t_coder	**coders;

// 	if (!table || !table -> coders || !table -> coders[0])
// 	{
// 		printf("Coders array is empty or NULL.\n");
// 		return ;
// 	}
// 	coders = table -> coders;
// 	printf("=========================================\n");
// 	printf("                  DATA                   \n");
// 	printf("=========================================\n");
// 	print_data(coders[0]-> data);
// 	printf("=========================================\n");
// 	printf("             CODERS STATUS               \n");
// 	printf("=========================================\n");
// 	i = 0;
// 	while (coders[i])
// 	{
// 		print_coder(coders[i]);
// 		i++;
// 	}
// 	printf("=========================================\n");
// }
