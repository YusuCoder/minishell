/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/15 23:45:52 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_str(char c)
{
	if (c == SPACE)
		return (1);
	else if (c == TAB)
		return (1);
	else
		return (0);
}

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

int count_tokens(char token)
{
    if (token == PIPE || token == LESS || token == GREATER || token == AMP)
        return 1;
    else if (token == SQUOTE || token == DQUOTE)
        return 2;
    else if (token == DOLLAR)
        return 3;
    return 0;
}

int count_words(const char *str, int i)
{
    int counter = 0;

    if (is_empty(str))
        return 0;

    while (str[i])
    {
        while (count_str(str[i]))
            i++;
        if (str[i] == '\0')
            return counter;

        if (get_word_len(str, i) != -1)
        {
            i += get_word_len(str, i) + 1;
            counter++;
            continue;
        }

        if (count_tokens(str[i]) == 2) // Quoted token
        {
            i += matching_quotes(str + i);
            counter++;
        }
        else
        {
            while (str[i] && !count_str(str[i]) && count_tokens(str[i]) != 1)
                i++;
            counter++;
        }
        if (count_str(str[i]))
            i++;
    }
    return counter;
}

// int	count_words(const char *str, int i)
// {
// 	int	counter;

// 	counter = 0;
// 	if (is_empty(str))
// 		return (0);
// 	while (str[i])
// 	{
// 		while (count_str(str[i]))
// 			i++;
// 		if (str[i] == '\0')
// 			return (counter);
// 		if (get_word_len(str, i) != -1)
// 		{
// 			i += get_word_len(str, i) + 1;
// 			counter++;
// 			continue ;
// 		}
// 		while (str[i] && !count_str(str[i]) && count_tokens(str[i]) != 1)
// 			i += matching_quotes(str + i) + 1;
// 		counter++;
// 		if (count_str(str[i]))
// 			i++;
// 	}
// 	return (counter);
// }
