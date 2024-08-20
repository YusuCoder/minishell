/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 20:21:50 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && count_str(str[i]))
	{
		i++;
	}
	if (i == (int)ft_strlen(str))
	{
		return (1);
	}
	return (0);
}

int	get_word_len(const char *str, int i)
{
	if (*(str + i) == PIPE || *(str + i) == AMP)
		return (0);
	if (i < (int)ft_strlen(str))
	{
		if (*(str + i) == GREATER && *(str + i + 1) == GREATER)
			return (1);
		else if (*(str + i) == LESS && *(str + i + 1) == LESS)
			return (1);
		else if (*(str + i) == GREATER || *(str + i) == LESS)
			return (0);
	}
	return (-1);
}

int	count_tokens(char token)
{
	if (token == PIPE || token == LESS || token == GREATER || token == AMP)
		return (1);
	else if (token == SQUOTE || token == DQUOTE)
		return (2);
	return (0);
}

int	process_token(const char *str, int *i)
{
	int	len;

	len = 0;
	while (count_str(str[*i]))
		(*i)++;
	if (str[*i] == '\0')
		return (0);
	len = get_word_len(str, *i);
	if (len != -1)
	{
		*i += len + 1;
		return (1);
	}
	if (count_tokens(str[*i]) == 2)
	{
		*i += matching_quotes(str + *i);
		return (1);
	}
	while (str[*i] && !count_str(str[*i]) && count_tokens(str[*i]) == 0)
		(*i)++;
	return (1);
}

int	count_words(const char *str, int i)
{
	int	counter;

	counter = 0;
	if (is_empty(str))
		return (0);
	while (str[i])
	{
		counter += process_token(str, &i);
		while (count_str(str[i]))
			i++;
	}
	return (counter);
}
