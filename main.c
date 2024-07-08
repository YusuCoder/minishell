/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:46:35 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/08 17:59:29 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(void)
{
	char	*line;

	line = NULL;
	while(1)
	{
		line = readline("minshell> ");
		if (!line)
			break ;
		else
			printf("Welcome to MINISHELL!\n");
	}
	return (0);
}
