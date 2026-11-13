/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:16:03 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/13 11:33:17 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	add_first_text(t_coder *coder, char *text, long long time, int id)
{
	t_text		*new_text;

	new_text = ft_calloc(sizeof(t_text), 1);
	if (!new_text)
		return ;
	new_text -> text = text;
	new_text -> id = id;
	new_text -> time = time - coder -> first_compile_start;
	new_text -> next = coder -> table -> text;
	if (coder -> table -> text)
	{
		coder -> table -> text -> prev = new_text;
		new_text -> next = coder -> table -> text;
	}
	coder -> table -> text = new_text;
}

t_text	*get_min_time_text(t_table *table)
{
	t_text	*current;
	t_text	*min_time_text;

	current = table -> text;
	if (!current)
		return (NULL);
	min_time_text = current;
	while (current)
	{
		if (current -> time <= min_time_text -> time)
			min_time_text = current;
		current = current -> next;
	}
	return (min_time_text);
}

void	free_min_time_text(t_table *table)
{
	t_text	*current;

	current = get_min_time_text(table);
	if (!current)
		return ;
	if (current -> prev)
		current -> prev -> next = current -> next;
	else
		table -> text = current -> next;
	if (current -> next)
		current -> next -> prev = current -> prev;
	free(current);
}

void	free_texts(t_table *table)
{
	t_text	*current;
	t_text	*next;

	current = table -> text;
	while (current)
	{
		next = current -> next;
		free(current);
		current = next;
	}
	table -> text = NULL;
}

int	print_text(t_table *table)
{
	char	*leter;
	int		result;
	t_text	*text;

	if (!table)
		return (0);
	text = get_min_time_text(table);
	if (!text)
		return (1);
	printf("%lli %i %s", text -> time, text -> id, text -> text);
	leter = "has burned out\n";
	result = ft_strcmp(text -> text, leter);
	free_min_time_text(table);
	return (result != 0);
}
