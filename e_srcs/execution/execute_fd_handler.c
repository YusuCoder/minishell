/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fd_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:37:31 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/26 15:39:42 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_origin_fd(t_data *data)
{
	data->fd_stdin = dup(STDIN_FILENO);
	data->fd_stdout = dup(STDOUT_FILENO);
}

void	set_origin_fd(t_data *data)
{
	if (dup2(data->fd_stdin, STDIN_FILENO) == -1)
		free_exit(data, 1);
	close(data->fd_stdin);
	if (dup2(data->fd_stdout, STDOUT_FILENO) == -1)
		free_exit(data, 1);
	close(data->fd_stdout);
}
