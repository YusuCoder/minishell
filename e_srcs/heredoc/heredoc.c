/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:36:26 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/25 00:17:48 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_save_input(t_cmd *cmd, char *line)
{
	char	*temp;

	if (cmd->heredoc_input == NULL)
		cmd->heredoc_input = ft_strjoin(line, "\n");
	else
	{
		temp = my_strjoin(cmd->heredoc_input, line, "\n");
		if (temp == NULL)
			return (-1);
		free(cmd->heredoc_input);
		cmd->heredoc_input = temp;
	}
	return (0);
}

int	heredoc_readline(t_cmd *cmd, char *delimiter, t_status status, char **env,
		t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (-1);
		expand_heredoc(&line, env, data);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (status == SAVE)
		{
			if (heredoc_save_input(cmd, line) == -1)
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	return (0);
}

void	heredoc_input_handler(t_data *data, t_cmd *cmd)
{
	t_redir	*current;
	char	*delimeter;

	current = cmd->input_list;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			delimeter = current->name;
			if (current->next != NULL)
			{
				if (heredoc_readline(cmd, delimeter, SKIP, data->env, data) ==
					-1)
					free_exit(data, 1);
			}
			else
			{
				if (heredoc_readline(cmd, delimeter, SAVE, data->env, data) ==
					-1)
					free_exit(data, 1);
			}
		}
		current = current->next;
	}
}

void	heredoc_handler(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	while (current != NULL)
	{
		if (current->is_heredoc == 1)
			heredoc_input_handler(data, current);
		current = current->next;
	}
}
