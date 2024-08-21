/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:36:26 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 16:29:47 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_parent_process(int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		perror("dup2");
		exit(1);
	}
	close(pipe_fd[0]);
	wait(NULL);
}

void	heredoc_child_process(int pipe_fd[2], t_redir *redir)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->name) == 0) {
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	heredoc_set_output_value(int pipe_fd[2], t_redir *redir)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		heredoc_child_process(pipe_fd, redir);
	else
		heredoc_parent_process(pipe_fd);
	return (0);
}

int	heredoc_handler(t_redir *heredoc_list)
{
	t_redir	*current;
	int		pipe_fd[2];
	char	*line;

	current = heredoc_list;
	while (current)
	{
		if (current->next == NULL)
		{
			if (heredoc_set_output_value(pipe_fd, current) == -1)
				return (-1);
		}
		else
		{
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, current->name) == 0)
				{
					free(line);
					break ;
				}
				free(line);
			}
		}
		current = current->next;
	}
	return (0);
}
