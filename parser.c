/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 10:32:54 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 11:56:32 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coders.h"


static int	alpha_verif(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] < 65 || arg[i] > 122)
			return (0);
		else if (arg[i] > 90 && arg[i] < 97)
			return (0);
		i++;
	}
	if (strcmp(arg, "fifo") != 0 && strcmp(arg, "edf") != 0)
		return (0);
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
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_data(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 9)
	{
		fprintf(stderr, "argument no valid");
		return (0);
	}
	i++;
	while (argv[i + 1])
	{
		if (!numeric_verif(argv[i]))
		{
			fprintf(stderr, "argument no valid");
			return (0);
		}
		i++;
	}
	if (!alpha_verif(argv[i]))
	{
		fprintf(stderr, "argument no valid");
		return (0);
	}
	printf("argument valid");
	return (1);
}

int	main(int argc, char **argv)
{
	int		number_of_coders;
	t_data	*data;
	t_coder	**coders;
	char	*scheduler;

	if (valid_data(argc, argv))
	{
		argv++;
	}
	return (0);
}
