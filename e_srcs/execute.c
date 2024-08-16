/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/15 15:16:10 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	is_accessable(char *cmd_name, char **cmd_path, char **env)
{
	char	*path;
	char	**path_array;
	int		i;

	if (*cmd_path != NULL)
	{
		if (is_executable(*cmd_path))
			return (1);
		else
			return (-1);
	}
	path = env_value_get(env, "PATH");
	if (path == NULL)
		return (-1);
	path_array = ft_split(path, ':');
	i = 0;
	while (path_array[i])
	{
		*cmd_path = my_strjoin(path_array[i], "/", cmd_name);
		if (is_executable(*cmd_path))
			return (free_array(path_array), 1) ;
		free(*cmd_path);
		i++;
	}
	return (free_array(path_array), 0);
}

void	execute_external(t_data *data, t_cmd *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	int		result;

	cmd_name = cmd->args[0];
	cmd_path = set_cmd_path(cmd_name);
	result = is_accessable(cmd_name, &cmd_path, data->env);
	if (result == 1)
	{
		free(cmd_path);
		if (execve(cmd_path, cmd->args, data->env) == -1)
		{
			perror("execve");
			free_exit(data, *data->exit_code);
		}
	}
	else if (result == -1)
		print_wrong_path(cmd_name, data->exit_code);
	else if (result == 0)
		print_wrong_command(cmd_name, data->exit_code);
}

void	execute_single_command(t_data *data, t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		execute_builtin(data, cmd->args);
	else
		execute_external(data, cmd);
}

void	execute(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	if (data->cmd_num == 0)
	{
		data->exit_code = 0;
		return ;
	}
	else if (data->cmd_num == 1)
	{
		if (is_builtin_cmd_only(data))
			return (clean_tokens(data));
		else
			execute_single_command(data, current);
	}
	else
	{
		while (current != NULL)
		{
			execute_single_command(data, current);
			current = current->next;
		}
	}
	clean_tokens(data);
}
