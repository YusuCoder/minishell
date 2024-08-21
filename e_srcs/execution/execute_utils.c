/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:09:08 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 16:28:55 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_pipe_fd(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(cmd->pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	else
	{
		cmd->pipe_fd[0] = -1;
		cmd->pipe_fd[1] = -1;
	}
	return (0);
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
