/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:18:32 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/18 19:20:49 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_list_last(t_cmd *head)
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

void	cmd_list_add(t_cmd *head, t_cmd *new)
{
	t_cmd	*current;

	if (head == NULL || new == NULL)
		return ;
	else
	{
		current = cmd_list_last(head);
		current->next = new;
	}
}

int	cmd_list_len(t_cmd *head)
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
