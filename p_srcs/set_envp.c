
#include "../includes/minishell.h"

// int	get_len(char **str)
// {
// 	int			i;
// 	char	*temp;

// 	i = 0;
// 	temp = *str;
// 	while (temp != NULL)
// 	{
// 		i++;
// 		temp = temp->next;
// 	}
// 	return (i);
// }

// char	**set_envp(t_ryusupov **envp)
// {
// 	t_ryusupov  *temp;
// 	char		**env;
// 	int			size;
// 	int			i;

// 	i = 0;
// 	if (envp == NULL || *envp == NULL)
// 		return (NULL);
// 	temp = *envp;
// 	size = get_len(envp);
// 	env = (char **)malloc((size + 1) * sizeof(char *));
// 	if (!env)
// 		return (NULL);
// 	while (i < size)
// 	{
// 		env[i] = temp->content;
// 		i++;
// 		temp = temp->next;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }




// int main(void)
// {
//     // Create linked list nodes
//     t_ryusupov *node1 = malloc(sizeof(t_ryusupov));
//     t_ryusupov *node2 = malloc(sizeof(t_ryusupov));
//     t_ryusupov *node3 = malloc(sizeof(t_ryusupov));

//     // Assign content to nodes
//     node1->content = strdup("PATH=/usr/bin");
//     node1->next = node2;

//     node2->content = strdup("HOME=/home/user");
//     node2->next = node3;

//     node3->content = strdup("SHELL=/bin/bash");
//     node3->next = NULL;

//     // Create a pointer to the head of the list
//     t_ryusupov *head = node1;

//     // Test get_len function
//     int length = get_len(&head);
//     printf("Length of linked list: %d\n", length);

//     // Test set_envp function
//     char **env = set_envp(&head);

//     // Print the resulting array of environment variables
//     if (env)
//     {
//         for (int i = 0; env[i] != NULL; i++)
//         {
//             printf("env[%d]: %s\n", i, env[i]);
//         }

//         // Free the allocated memory for env array
//         free(env);
//     }

//     // Free the allocated memory for nodes
//     free(node1->content);
//     free(node2->content);
//     free(node3->content);
//     free(node1);
//     free(node2);
//     free(node3);

//     return (0);
// }
