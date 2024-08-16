/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:17:37 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 12:18:26 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arguments(char **tokens, int index)
{
	int	counter;

	counter = 0;
	while (tokens[index] && ft_strncmp(tokens[index], "|", 1) != 0)
	{
		counter++;
		index++;
	}
	return (counter);
}

int	count_commands(char **tokens)
{
	int	counter;
	int	i;

	counter = 1;
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
			counter++;
		i++;
	}
	return (counter);
}

char	**cmd_list_set_args(char **tokens, int len, int index)
{
	char	**cmd_args;
	int		i;

	cmd_args = (char **)malloc((len + 1) * sizeof(char *));
	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cmd_args[i] = ft_strdup(tokens[index]);
		if (!cmd_args[i])
		{
			while (i > 0)
				free(cmd_args[--i]);
			free(cmd_args);
			return (NULL);
		}
		i++;
		index++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

void	cmd_list_add_new(t_cmd **head, char **tokens, int len, int index)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		exit(EXIT_FAILURE);
	new_cmd->args = cmd_list_set_args(tokens, len, index);
	new_cmd->args_num = len;
	new_cmd->is_heredoc = 0;
	new_cmd->hrdc_delimeter = NULL;
	new_cmd->is_redir_input = 0;
	new_cmd->is_redir_output = 0;
	new_cmd->file_input = NULL;
	new_cmd->file_output = NULL;
	new_cmd->is_output_append = 0;
	new_cmd->next = NULL;
	if (*head == NULL)
		*head = new_cmd;
	else
	{
		current = list_get_last(*head);
		current->next = new_cmd;
	}
}

void	cmd_list_create(char **tokens, t_data *data)
{
	int		args_num;
	int		cmds_num;
	int		i;

	if (!tokens || !data)
		exit(EXIT_FAILURE);
	cmds_num = count_commands(tokens);
	data->cmd_num = cmds_num;
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
			i++;
		else
		{
			args_num = count_arguments(tokens, i);
			cmd_list_add_new(&data->cmd_list, tokens, args_num, i);
			i = i + args_num;
		}
	}
}
