/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/23 21:17:38 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_data *data, t_cmd *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	int		result;

	if (redirection_handler(cmd, data->exit_code) == -1)
		free_exit(data, 1) ;
	cmd_name = cmd->cmd_array[0];
	cmd_path = set_cmd_path(cmd_name);
	result = is_accessable(cmd_name, &cmd_path, data->env);
	if (result == -1)
		print_wrong_path(cmd_name, data->exit_code);
	else if (result == 0)
		print_wrong_command(cmd_name, data->exit_code);
	else if (result == 1)
	{
		if (execve(cmd_path, cmd->cmd_array, data->env) == -1)
		{
			free(cmd_path);
			free_error_exit(data, *data->exit_code, "execve");
		}
		free(cmd_path);
	}
}

void	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	result;

	result = 0;
	if (redirection_handler(cmd, data->exit_code) == -1)
		free_exit(data, 1);
	if (is_cd(cmd->cmd_array[0]))
		result = execute_cd(cmd->cmd_array, data->env, data->exit_code);
	else if (is_pwd(cmd->cmd_array[0]))
		result = execute_pwd(data->exit_code);
	else if (is_env(cmd->cmd_array[0]))
		result = execute_env(data->env, data->exit_code);
	else if (is_echo(cmd->cmd_array[0]))
		result = execute_echo(cmd->cmd_array, data->exit_code);
	else if (ft_strcmp(cmd->cmd_array[0], "export") == 0)
		result = execute_export(cmd->cmd_array, &data->env, data->exit_code);
	else if (ft_strcmp(cmd->cmd_array[0], "unset") == 0)
		result = execute_unset(cmd->cmd_array, &data->env, data->exit_code);
	else if (ft_strcmp(cmd->cmd_array[0], "exit") == 0)
		execute_exit(data, cmd->cmd_array, data->exit_code);
	if (result == -1)
		free_exit(data, *data->exit_code);
	else
		return ;
}

void	execute_single_command(t_data *data, t_cmd *cmd, t_status status)
{
	if (cmd->cmd_array[0] == NULL)
	{
		if (redirection_handler(cmd, data->exit_code) == -1)
			free_exit(data, 1);
		return ;
	}
	else
	{
		if (is_builtin(cmd->cmd_array[0]))
			execute_builtin(data, cmd);
		else
		{
			if (status == ONE)
				fork_external(data, cmd);
			else if (status == MULTIPLE)
				execute_external(data, cmd);
		}
	}
}

void	execute_multiple_commands(t_data *data)
{
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*current;

	current = data->cmd_list;
	if (pipe_set_all(data->cmd_list) == -1)
		free_exit(data, 1);
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			pipe_redirection_handler(data, current);
			execute_single_command(data, current, MULTIPLE);
			free_exit(data, *data->exit_code);
		}
		else if (pid > 0)
			last_pid = pid;
		else
			free_error_exit(data, 1, "fork");
		current = current->next;
	}
	pipe_close_all(data->cmd_list);
	wait_processes(last_pid, data->exit_code);
}

void	execute(t_data *data)
{
	_handle_signals(CHILD_PROCESS, data);
	if (data == NULL || data->cmd_list == NULL)
		return ;
	if (data->cmd_num == 1)
		execute_single_command(data, data->cmd_list, ONE);
	else
		execute_multiple_commands(data);
	cleanup(data);
}
