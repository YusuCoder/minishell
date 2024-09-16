/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/26 15:44:12 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Terminal ctrl setting disables echo messages of
	ctrl signals using flag ECHOCTRL
*/

void	_handle_child_signal(int signal)
{
	if (signal == SIGINT)
	{
		return ;
	}
	if (signal == SIGQUIT)
	{
		return ;
	}
	return ;
}

// Signal handler for other signals
void	_handle_other_signals(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	_handle_signals(t_process stats)
{
	struct sigaction	sa;

	if (stats == CHILD_PROCESS)
	{
		sa.sa_handler = &_handle_child_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			return ;
	}
	else
	{
		sa.sa_handler = &_handle_other_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return ;
	}
}

void	_init_terminal(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
}
