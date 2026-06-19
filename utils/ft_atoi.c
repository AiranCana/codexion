/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:19:35 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 16:01:40 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		++nptr;
	if (0 == ft_isdigit(*nptr))
	{
		if (*nptr == '+' || *nptr == '-')
		{
			if (*nptr == '-')
				sign *= -1;
		}
		else
			return (0);
		++nptr;
	}
	while (*nptr && 0 != ft_isdigit(*nptr))
	{
		num *= 10;
		num += (*(nptr++) - 48);
	}
	return (num * sign);
}
