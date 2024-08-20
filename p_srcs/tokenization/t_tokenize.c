/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 20:21:45 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	In this function im checking for the quotes "" or '' if the current
	idex is " or ' then
	the function iterates through the string untill it finds
	the closing quote to return its index
*/
int	matching_quotes(const char *str)
{
	int		i;
	char	quote_type;

	i = 1;
	quote_type = str[0];
	while (str[i] && str[i] != quote_type)
	{
		i++;
	}
	if (str[i] == quote_type)
	{
		i++;
	}
	return (i);
}

int	count_str(char c)
{
	if (c == SPACE)
		return (1);
	else if (c == TAB)
		return (1);
	else
		return (0);
}

char	**tokenizing(const char *str)
{
	char	**t;
	int		words;
	int		i;
	int		num_tokens;

	if (!str)
		return (NULL);
	i = 0;
	words = count_words(str, i);
	if (words < 1)
		return (NULL);
	t = (char **)malloc(sizeof(char *) * (words + 1));
	if (!t)
		return (NULL);
	num_tokens = take_tokens(t, str, 0);
	if (num_tokens < 0)
	{
		free_array(t);
		return (NULL);
	}
	t[num_tokens] = NULL;
	return (t);
}

// int	main(void)
// {
// 	const char	*str;
// 	char		**tokens;
// 	int			i;

// 	str = "echo \"-\"l";
// 	tokens = tokenizing(str);
// 	if (tokens)
// 	{
// 		i = 0;
// 		while (tokens[i])
// 		{
// 			printf("[ %s ]   ", tokens[i]);
// 			i++;
// 		}
// 		free(tokens);
// 	}
// 	return (0);
// }
