/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:09 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 12:26:49 by tkubanyc         ###   ########.fr       */
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
