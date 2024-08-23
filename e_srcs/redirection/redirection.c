/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:33:40 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/23 21:17:39 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_input_handler(t_redir *input_list, int *exit_code)
{
	t_redir	*current;
	int		fd;

	current = input_list;
	while (current)
	{
		fd = open(current->name, O_RDONLY);
		if (fd == -1)
		{
			ft_perror("minishell: ", current->name, \
						": No such file or directory");
			*exit_code = 1;
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			perror("minishell: dup2");
			return (-1);
		}
		close(fd);
		current = current->next;
	}
	return (0);
}

int	redir_output_handler(t_redir *output_list)
{
	t_redir	*current;
	int		fd;

	current = output_list;
	while (current)
	{
		if (current->is_append)
			fd = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			perror("dup2");
			return (-1);
		}
		close(fd);
		current = current->next;
	}
	return (0);
}

int	redirection_handler(t_cmd *cmd, int *exit_code)
{
	if (cmd->is_redir_input && cmd->input_list)
	{
		if (redir_input_handler(cmd->input_list, exit_code) == -1)
			return (-1);
	}
	if (cmd->is_redir_output && cmd->output_list)
	{
		if (redir_output_handler(cmd->output_list) == -1)
			return (-1);
	}
	return (0);
}
