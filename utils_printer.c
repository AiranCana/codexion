/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanadil <acanadil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:16:03 by acanadil          #+#    #+#             */
/*   Updated: 2026/11/05 16:29:09 by acanadil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	add_first_text(t_coder *coder, char *text, long long time, int id)
{
	t_text		*new_text;
	long long	new_time;

	if (coder -> table -> text == NULL)
	{
		new_time = time - coder -> first_compile_start;
		coder -> table -> text = malloc(sizeof(t_text));
		if (!coder -> table -> text)
			return ;
		coder -> table -> text -> text = text;
		coder -> table -> text -> id = id;
		coder -> table -> text -> time = new_time;
		coder -> table -> text -> next = NULL;
	}
	else
	{
		new_text = malloc(sizeof(t_text));
		if (!new_text)
			return ;
		new_text -> text = text;
		new_text -> id = id;
		new_text -> time = time;
		new_text -> next = coder -> table -> text;
		coder -> table -> text = new_text;
	}
}

t_text	*get_last_text(t_table *table)
{
	t_text	*current;

	current = table -> text;
	while (current && current -> next)
		current = current -> next;
	if (current)
		return (current);
	return (NULL);
}

void	free_last_text(t_table *table)
{
	t_text	*current;
	t_text	*prev;

	current = table -> text;
	prev = NULL;
	while (current && current -> next)
	{
		prev = current;
		current = current -> next;
	}
	if (prev)
		prev -> next = NULL;
	if (current)
	{
		free(current -> text);
		free(current);
	}
}

void	free_texts(t_table *table)
{
	t_text	*current;
	t_text	*next;

	current = table -> text;
	while (current)
	{
		next = current -> next;
		free(current -> text);
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
	text = get_last_text(table);
	if (!text)
		return (1);
	printf("%lli %i %s", text -> time, text -> id, text -> text);
	leter = "has burned out\n";
	result = ft_strcmp(text -> text, leter);
	free_last_text(table);
	return (result != 0);
}
