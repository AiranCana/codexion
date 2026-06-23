/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 10:32:54 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/23 12:29:39 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coders.h"
#include "utils/utils.h"
#include "generate/generate.h"

static int	alpha_verif(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]))
			return (0);
		i++;
	}
	if (strcmp(arg, "fifo") != 0 && ft_strlen(arg) != 4)
	{
		if (strcmp(arg, "edf") != 0 && ft_strlen(arg) != 3)
			return (0);
	}
	return (1);
}

static int	numeric_verif(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	valid_data(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 8)
	{
		printer_error("");
		return (0);
	}
	while (argv[i + 1])
	{
		if (!numeric_verif(argv[i]))
		{
			printer_error("Invalid argument: not a number");
			return (0);
		}
		i++;
	}
	if (!alpha_verif(argv[i]))
	{
		printer_error("Invalid argument: not a valid scheduler type");
		return (0);
	}
	printf("argument valid\n");
	return (1);
}

static t_data	*gen_data(int argc, char **argv)
{
	t_data	*data;

	if (valid_data(argc, argv))
	{
		data = init_data(argc, argv);
		if (!data)
			return (NULL);
		return (data);
	}
	return (NULL);
}

t_coder	**init_coders(int argc, char **argv)
{
	t_data	*data;
	t_coder	**coders;
	int		i;
	int		num_coders;

	i = 0;
	if (argc != 8)
		return (NULL);
	data = gen_data(argc, argv);
	if (!data)
		return (NULL);
	num_coders = atoi(argv[0]);
	coders = ft_calloc(sizeof(t_coder *), (num_coders + 1));
	if (!coders)
		return (NULL);
	while (i < num_coders)
	{
		coders[i] = gen_coder(i + 1, data);
		if (!coders[i])
			return (delet_coders(coders));
		i++;
	}
	return (coders);
}
