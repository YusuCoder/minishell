
#include "../includes/minishell.h"

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
	array = NULL;
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
	data = NULL;
}

void	free_exit(t_data *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}
