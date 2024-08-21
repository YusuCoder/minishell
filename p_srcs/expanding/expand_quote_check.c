/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:28:16 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/21 21:29:04 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_left_quote(char *token, int i)
{
	int	left;

	left = 0;
	while (i >= 0)
	{
		if (token[i] == '\'')
		{
			left = 1;
			break ;
		}
		i--;
	}
	return (left);
}

static int	check_right_quote(char *token, int i)
{
	int	right;

	right = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			right = 1;
			break ;
		}
		i++;
	}
	return (right);
}

int	not_in_squote(char *token, int i)
{
	int	left;
	int	right;

	left = check_left_quote(token, i - 1);
	right = check_right_quote(token, i + 1);
	if (right && left)
		return (0);
	return (1);
}
