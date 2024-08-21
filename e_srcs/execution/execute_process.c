/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:24 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 16:28:53 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_child_process(t_data *data, t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
		close(*prev_fd);
	}
	if (cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
		close(cmd->pipe_fd[1]);
	}
	if (cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	// if (handle_redirection(cmd) == -1)
	// 	free_exit(data, *data->exit_code);
	execute_single_command(data, cmd);
	free_exit(data, *data->exit_code);
}

void	run_parent_process(t_cmd *cmd, int *prev_fd)
{
	wait(NULL);
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->pipe_fd[0] != -1)
	{
		*prev_fd = cmd->pipe_fd[0];
		close(cmd->pipe_fd[1]);
	}
}

// ls "-"l

// parser:
// string

// s t r i n g
// if character = "" then read until next "" -> save type of "" as info then delete if not nested ""
// if character = '' then read until next '' -> save type of '' as info then delete if not nested ''
// if character = $ then if next after = ' ' then -> print $
// 						or if next after = alphanumeric then -> expand
// 						or if next after = ? then status_code insert here
// if character = alphanumeric as long as no space -> make tok until space
// if character = >> << < > then handle as needed
// if character = | start new command

// after each new token check if previous token was the same type or same expanderfeature and no space between
// if yes, write together.

// "hello"$world$stuff$echo'lol'

// ->helloexpandedvalofworldexpandedvalueofstuffexpandedvalueofecholol

// for example export E=e C=c H=h O=o $E$C$H$O becomes echo

// so $h$o both are expandable
