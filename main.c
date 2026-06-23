/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:51:03 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/23 12:59:28 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "utils/utils.h"
#include "generate/generate.h"
#include <stdio.h>

void	free_split(char ***args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		free(args[0][i]);
		args[0][i] = NULL;
		i++;
	}
	free(args[0]);
	args[0] = NULL;
}

int	printer_error(char *message)
{
	if (message[0] == '\0')
		fprintf(stderr, "Error: Invalid number of arguments\n");
	else
		fprintf(stderr, "Error: %s\n", message);
	return (0);
}

void	*freeser(int split, char ***argv, t_coder **cod, t_USB **us)
{
	if (split && argv)
		free_split(argv);
	if (cod)
		delet_coders(cod);
	if (us)
		delet_usbs(us);
	printer_error("Memory allocation failed");
	return (NULL);
}

void	*execute_program(int argc, char ***argv, int spliter)
{
	t_coder	**coders;
	t_USB	**usb;
	t_table	*table;

	coders = init_coders(argc, *argv);
	if (!coders)
		return (freeser(spliter, argv, NULL, NULL));
	usb = gen_usbs(ft_structurlen((const void **)coders));
	if (!usb)
		return (freeser(spliter, argv, coders, NULL));
	table = gen_table(coders);
	if (!table)
		return (freeser(spliter, argv, coders, usb));
	asign_usb(usb, coders);
	// print_all_coders(table);
	delet_usbs(usb);
	delete_table(table);
	return (NULL);
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
		arg = ft_structurlen((const void **) args);
		spliter = 1;
	}
	else if (argc == 9)
	{
		args = argv + 1;
		arg = argc - 1;
	}
	execute_program(arg, &args, spliter);
	if (spliter && args)
		free_split(&args);
	return (0);
}
