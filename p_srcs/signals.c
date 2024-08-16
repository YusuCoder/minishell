/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/17 00:22:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_last_signal_received = 0;

// Function to determine the exit code
void	determine_exit_code(int *exit_code)
{
	if (g_last_signal_received == SIGINT)
		*exit_code = 130;
	else if (g_last_signal_received == SIGQUIT)
		*exit_code = 131;
	else
		*exit_code = 0;
}
/*Terminal ctrl setting disables echo messages of ctrl signals using flag ECHOCTRL*/
void	_handle_child_signal(int signal)
{
	g_last_signal_received = signal;
	if (signal == SIGINT)
	{
		write(1, "^C\n", 3);
	}
	if (signal == SIGQUIT)
	{
		write(1, "^\\Quit: 3\n", 10);
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

// Function to handle signals setup
void	_handle_signals(t_process stats)
{
	struct sigaction	sa;

	if (stats == CHILD_PROCESS)
	{
		sa.sa_handler = &_handle_child_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit(-1);
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			exit(-1);
	}
	else
	{
		sa.sa_handler = &_handle_other_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit(-1);
		if (signal(SIGQUIT, SIG_IGN) < 0)
			exit(-1);
	}
}

void	_init_terminal(int exit_code)
{
	(void)exit_code;
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
}
