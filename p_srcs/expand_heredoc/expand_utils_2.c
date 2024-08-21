/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:03:18 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/21 20:15:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_string_heredoc(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]))
			break ;
		i++;
	}
	return (i);
}

int	still_dollar_heredoc(char *token)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (token[i])
	{
		if (token[i] == '$')
			check = 1;
		i++;
	}
	if (check > 0)
		return (1);
	else
		return (0);
}
