
#include "../includes/minishell.h"

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

void	list_free(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = *head;
	while (current != NULL)
	{
		i = 0;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

// void	list_clean(t_cmd *head)
// {
// 	t_cmd	*current;
// 	int		i;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		i = 0;
// 		while (current->args[i])
// 		{
// 			free(current->args[i]);
// 			i++;
// 		}
// 		free(current->args);
// 		free(current);
// 		current = current->next;
// 	}
// 	head = NULL;
// }
