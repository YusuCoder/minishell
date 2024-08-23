/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:36:26 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/21 20:41:07 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_readline(char **env, char *delimeter, int fd, t_status status)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(GREEN"> "RESET);
		if (line == NULL)
		{
			if (status == REDIRECT)
				return (-1);
		}
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		if (status == REDIRECT)
		{
			printf("%s\n", env[0]);
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	return (0);
}

int	heredoc_redirect(char **env, char *delimeter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (heredoc_readline(env, delimeter, pipe_fd[1], REDIRECT) == -1)
	{
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		perror("dup2");
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

int heredoc_handler(char **env, t_redir *heredoc_list, t_status status)
{
	t_redir	*current;
	char	*delimeter;

	current = heredoc_list;
	while (current != NULL)
	{
		delimeter = current->name;
		if (status == REDIRECT && current->next == NULL)
		{
			if (heredoc_redirect(env, delimeter) == -1)
				return (-1);
		}
		else
		{
			if (heredoc_readline(NULL, delimeter, -1, SKIP) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
