/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_handle_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:28:23 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/12 09:23:40 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*---SIGNALS FOR INTERACTIVE MODE, SIGINT = CTRL+C, SIGQUIT = CTRL+\---*/
void	_handle_child_signal(int signal)
{
	if (signal == SIGINT)
		gl_command.exit_code = 130;
	if (signal == SIGQUIT)
		gl_command.exit_code = 131;
	return ;
}

void	_handle_other_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		gl_command.exit_code = 1;
	}
	else
		return ;
}
/*if the signal came in interactive mode do it otherwise ignore the quit signal*/
void	_handle_signals(t_process stats)
{
	struct sigaction	sa;

	if (stats == CHILD_PROCESS)
	{
		sa.sa_handler = &_handle_child_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit(EXIT_FAILURE);
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			exit(EXIT_FAILURE);
	}
	else
	{
		sa.sa_handler = &_handle_other_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit(EXIT_FAILURE);
		if (signal(SIGQUIT, SIG_IGN) < 0)
			exit(EXIT_FAILURE);
	}
}
