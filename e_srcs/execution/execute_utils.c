/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:09:08 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/23 20:55:23 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_external(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == 0)
	{
		execute_external(data, cmd);
		free_exit(data, *data->exit_code);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			*data->exit_code = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			*data->exit_code = WTERMSIG(exit_status) + 128;
	}
	else
		free_error_exit(data, 1, "fork");
}

char	*set_cmd_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (str);
		i++;
	}
	return (NULL);
}

void	print_wrong_command(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": command not found");
	*exit_code = 127;
}

void	print_wrong_path(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": No such file or directory");
	*exit_code = 127;
}
