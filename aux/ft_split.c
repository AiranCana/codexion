/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:59:55 by acanadil          #+#    #+#             */
/*   Updated: 2026/06/18 15:25:22 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aux.h"

static void	release(char **sol, size_t len)
{
	int	i;

	i = len;
	while (i >= 0)
		free(sol[i--]);
	free(sol);
}

static int	spliter(char *str, char c, int sections, char **sol)
{
	int	i;
	int	j;

	i = 0;
	while (sections > i)
	{
		j = 0;
		while (str[j] && str[j] != c)
			j++;
		sol[i] = ft_substr(str, 0, j);
		if (!sol[i])
		{
			release(sol, i);
			return (0);
		}
		while (str[j] && str[j] == c)
			j++;
		str = &str[j];
		i++;
	}
	sol[i] = NULL;
	return (1);
}

static int	countleter(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			++count;
			while (s[i] && s[i] == c)
				i++;
		}
		++i;
	}
	return (++count);
}

static char	**returned(char *str, char **ret)
{
	if (!str && ret)
	{
		free(ret);
		ret = NULL;
	}
	if (str)
		free(str);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		sections;
	char	**sol;
	char	*str;
	char	leter[2];

	if (!s)
		return (NULL);
	leter[0] = c;
	leter[1] = '\0';
	str = ft_strtrim(s, leter);
	sections = countleter(str, c);
	if (!sections)
		return (returned(str, ft_calloc(sizeof (char *), 1)));
	sol = ft_calloc((sections + 1), sizeof (char *));
	if (sol)
	{
		if (!spliter(str, c, sections, sol))
			return (returned(str, NULL));
	}
	free(str);
	return (sol);
}
