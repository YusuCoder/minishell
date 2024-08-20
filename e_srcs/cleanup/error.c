/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:09 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/18 18:53:23 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *msg1, char *arg, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (arg != NULL)
		write(2, arg, ft_strlen(arg));
	if (msg2 != NULL)
		write(2, msg2, ft_strlen(msg2));
	write(2, "\n", 1);
}

void	ft_perror_parsing(char *msg1, char *msg2, char *arg, int *exit_code)
{
	char backtrick = 96;

	write(2, msg1, ft_strlen(msg1));
	if (msg2 != NULL)
		write(2, msg2, ft_strlen(msg2));
	if (arg != NULL)
	{
		write(1, &backtrick, 1);
		write(2, arg, ft_strlen(arg));
		write(1, "'", 1);
	}
	write(2, "\n", 1);
	*exit_code = 258;
}
