/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:28:16 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/23 14:47:29 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Checks if the character at index i is inside double quotes
static int	is_in_double_quotes(char *token, int i)
{
	int	dbl_quote_count;
	int	j;

	dbl_quote_count = 0;
	j = 0;
	while (j < i)
	{
		if (token[j] == '\"')
			dbl_quote_count++;
		j++;
	}
	return (dbl_quote_count % 2 != 0);
}

static int	check_left_quote(char *token, int i)
{
	int	left;

	left = 0;
	while (i >= 0)
	{
		if (token[i] == '\'' && !is_in_double_quotes(token, i))
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
		if (token[i] == '\'' && !is_in_double_quotes(token, i))
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
