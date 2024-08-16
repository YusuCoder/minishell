/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 14:46:43 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_list(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		free_array(current->args);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_all(t_data *data)
{
	if (data == NULL)
		return ;
	free_array(data->env);
	data->env = NULL;
	free_array(data->tokens);
	data->tokens = NULL;
	free_list(&data->cmd_list);
}

void	free_exit(t_data *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}

void	free_error_exit(t_data *data, int exit_code, char *error_msg)
{
	if (error_msg != NULL)
		perror(error_msg);
	free_exit(data, exit_code);
}
