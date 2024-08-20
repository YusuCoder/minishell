/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:05:44 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/17 14:29:01 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_cmd_only(t_data *data)
{
	if (data->cmd_num == 1
		&& is_builtin(data->cmd_list->args[0])
		&& data->cmd_list->is_heredoc == 0
		&& data->cmd_list->is_redir_input == 0
		&& data->cmd_list->is_redir_output == 0)
	{
		execute_builtin(data, data->cmd_list->args);
		return (1);
	}
	else
		return (0);
}

int	is_executable(char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, R_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (1);
		}
	}
	return (0);
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
	path_array = split_str(path, ':');
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
