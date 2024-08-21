/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 21:11:05 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_data *data, t_cmd *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	int		result;

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
			free_error_exit(data, *data->exit_code, "execve");
		free(cmd_path);
	}
}

void	execute_builtin(t_data *data, char **args)
{
	int	result;

	result = 0;
	if (is_cd(args[0]))
		result = execute_cd(args, data->env, data->exit_code);
	else if (is_pwd(args[0]))
		result = execute_pwd(data->exit_code);
	else if (is_env(args[0]))
		result = execute_env(data->env, data->exit_code);
	else if (is_echo(args[0]))
		result = execute_echo(args, data->exit_code);
	else if (ft_strcmp(args[0], "export") == 0)
		result = execute_export(args, &data->env, data->exit_code);
	else if (ft_strcmp(args[0], "unset") == 0)
		result = execute_unset(args, &data->env, data->exit_code);
	else if (ft_strcmp(args[0], "exit") == 0)
		execute_exit(data, args, data->exit_code);
	if (result == -1)
		free_exit(data, *data->exit_code);
	else
		return ;
}

void	execute_single_command(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->cmd_array == NULL)
	{
		if (redirection_handler(cmd) == -1)
			free_exit(data, 1);
		return ;
	}
	if (is_builtin(cmd->cmd_array[0]))
	{
		if (redirection_handler(cmd) == -1)
			free_exit(data, 1);
		execute_builtin(data, cmd->cmd_array);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (redirection_handler(cmd) == -1)
				free_exit(data, 1) ;
			execute_external(data, cmd);
			free_exit(data, *data->exit_code);
		}
		else if (pid > 0)
			wait(NULL);
		else
			free_error_exit(data, 1, "fork");
	}
}

void	execute_multiple_commands(t_data *data)
{
	t_cmd	*current;
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	current = data->cmd_list;
	while (current != NULL)
	{
		if (set_pipe_fd(current) == -1)
			free_exit(data, 1);
		pid = fork();
		if (pid == 0)
			run_child_process(data, current, &prev_fd);
		else if (pid > 0)
			run_parent_process(current, &prev_fd);
		else
			free_error_exit(data, 1, "fork");
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
}

void	execute(t_data *data)
{
	_handle_signals(CHILD_PROCESS);
	determine_exit_code(data->exit_code);
	if (data == NULL || data->cmd_list == NULL)
		return ;
	if (data->cmd_num == 0)
	{
		data->exit_code = 0;
		return ;
	}
	else if (data->cmd_num == 1)
	{
		if (is_builtin_cmd_only(data))
		{
			execute_builtin(data, data->cmd_list->cmd_array);
			return (cleanup(data));
		}
		else
			execute_single_command(data, data->cmd_list);
	}
	else
		execute_multiple_commands(data);
	cleanup(data);
}
