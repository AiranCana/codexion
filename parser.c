/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 10:32:54 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/17 13:32:32 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	numeric_verif(char *arg)
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

int	main(int argc, char **argv)
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char*	scheduler;

	if (argc != 9)
	{
		printf("no valid");
		return (0);
	}
	argv++;
	while (argv[1])
	{
		if (!numeric_verif(*argv))
		{
			printf("no valid");
			return (0);
		}
		argv++;
	}
	printf("valid");
	return (0);
}
