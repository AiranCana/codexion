/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:51:03 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/22 16:02:11 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "utils/utils.h"
#include "generate/generate.h"
#include <stdio.h>

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	printer_error(char *message)
{
	if (message[0] == '\0')
		fprintf(stderr, "Error: Invalid number of arguments\n");
	else
		fprintf(stderr, "Error: %s\n", message);
	return (0);
}

void	execute_program(int argc, char **argv, int spliter)
{
	t_coder	**coders;
	t_USB	**usb;

	coders = init_coders(argc, argv);
	if (!coders)
		return ;
	usb = gen_usbs(ft_structurlen((const void **)coders));
	if (!coders || !usb)
	{
		if (spliter)
			free_split(argv);
		if (coders)
			delet_coders(coders);
		if (usb)
			delet_usbs(usb);
		printer_error("Memory allocation failed");
		return ;
	}
	asign_usb(usb, coders);
	// print_all_coders(coders);
	delet_usbs(usb);
	delet_coders(coders);
}

int	main(int argc, char **argv)
{
	char	**args;
	int		arg;
	int		spliter;

	args = NULL;
	spliter = 0;
	if (argc != 9 && argc != 2)
		return (printer_error(""));
	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args)
			return (printer_error("Memory allocation failed"));
		arg = ft_memlen(args);
		spliter = 1;
	}
	else if (argc == 9)
	{
		args = argv + 1;
		arg = argc - 1;
	}
	execute_program(arg, args, spliter);
	if (spliter)
		free_split(args);
	return (0);
}
