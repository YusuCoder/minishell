/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 11:07:01 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_redir(t_redir **redir_list, int *redir_flag, char *name, t_type type)
{
	t_redir	*new_redir;

	if (*redir_flag == 0)
		*redir_flag = 1;
	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
		return (perror("malloc"), -1);
	if (name == NULL)
		new_redir->name = NULL;
	else
		new_redir->name = ft_strdup(name);
	if (type == APPEND)
		new_redir->is_append = 1;
	else
		new_redir->is_append = 0;
	new_redir->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_redir;
	else
		redir_list_add(*redir_list, new_redir);
	return (0);
}

int	redir_list_create(t_type type, t_cmd *cmd, int index)
{
	char	*name;
	int		result;

	result = 0;
	if (!is_redirection(cmd->args[index + 1]) || cmd->args[index + 1] != NULL)
		name = cmd->args[index + 1];
	else
		name = NULL;
	if (type == HEREDOC)
		result = new_redir(&cmd->heredoc_list, &cmd->is_heredoc, name, HEREDOC);
	else if (type == INPUT)
		result = new_redir(&cmd->input_list, &cmd->is_redir_input, name, INPUT);
	else if (type == APPEND)
		result = new_redir(&cmd->output_list, &cmd->is_redir_output, name, APPEND);
	else if (type == OUTPUT)
		result = new_redir(&cmd->output_list, &cmd->is_redir_output, name, OUTPUT);
	if (result == -1)
		return (-1);
	if (name == NULL)
		return (1);
	else
		return (2);
}

int	count_redir(char **args)
{
	int	redir_counter;
	int	i;

	redir_counter = 0;
	i = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
			redir_counter++;
		i++;
	}
	return (redir_counter);
}

int	redir_list_check(t_cmd *cmd)
{
	int		i;
	int		args_skip;
	int		redir_num;

	redir_num = count_redir(cmd->args);
	if (redir_num == 0)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		args_skip = 1;
		if (is_heredoc(cmd->args[i]))
			args_skip = redir_list_create(HEREDOC, cmd, i);
		else if (is_redir_input(cmd->args[i]))
			args_skip = redir_list_create(INPUT, cmd, i);
		else if (is_redir_append(cmd->args[i]))
			args_skip = redir_list_create(APPEND, cmd, i);
		else if (is_redir_otput(cmd->args[i]))
			args_skip = redir_list_create(OUTPUT, cmd, i);
		if (args_skip == -1)
			return (-1);
		else
			i = i + args_skip;
	}
	return (1);
}

void	redir_list_handler(t_data *data)
{
	t_cmd	*current;
	int		result;

	if (data == NULL || data->cmd_list == NULL)
		return ;
	current = data->cmd_list;
	while (current != NULL)
	{
		result = redir_list_check(current);
		if (result == -1)
			free_exit(data, 1);
		else if (result == 0)
		{
			current->cmd_array = array_copy(current->args);
			if (current->cmd_array == NULL)
				free_exit(data, 1);
		}
		else if (result == 1)
		{
			if (set_cmd_array(current) == -1)
				free_exit(data, 1);
		}
		current = current->next;
	}
}
