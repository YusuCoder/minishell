/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:18:32 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 12:18:34 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*list_get_last(t_cmd *head)
{
	t_cmd	*last;

	if (head == NULL)
		return (NULL);
	last = head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void	list_add_new(t_cmd **head, t_cmd *new)
{
	t_cmd	*current;

	if (head == NULL)
		*head = new;
	else
	{
		current = list_get_last(*head);
		current->next = new;
	}
}

int	list_len(t_cmd *head)
{
	int		length;
	t_cmd	*current;

	length = 0;
	current = head;
	while (current->next != NULL)
	{
		length++;
		current = current->next;
	}
	return (length);
}
