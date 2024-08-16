/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/15 12:25:13 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*In this function im checking for the quotes "" or '' if the current idex is " or ' then
  the function iterates through the string untill it finds the closing quote to return its index
*/
// int	matching_quotes(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == DQUOTE)
// 	{
// 		i++;
// 		while (str[i] != DQUOTE && str[i])
// 			i++;
// 	}
// 	else if (str[i] == SQUOTE)
// 	{
// 		i++;
// 		while (str[i] != SQUOTE && str[i])
// 			i++;
// 	}
// 	return (i);
// }

int matching_quotes(const char *str)
{
    int i = 0;
    if (str[i] == DQUOTE || str[i] == SQUOTE)
    {
        char quote_type = str[i];
        i++;
        while (str[i] && str[i] != quote_type)
            i++;
        if (str[i] == quote_type) // If we find the matching quote
            i++;
    }
    return i;
}

char **tokenizing(const char *str) {
    char **t;
    int words;
    int i;

    if (!str) {
        return NULL;
    }

    i = 0;
    words = count_words(str, i);
    if (words < 1) {
        return NULL;
    }

    t = (char **)malloc(sizeof(char *) * (words + 1)); // Corrected memory allocation
    if (!t) {
        return NULL;
    }

    int num_tokens = take_tokens(t, str, 0);
    if (num_tokens < 0) {
        // If take_tokens indicates an error, free allocated memory
        for (int j = 0; j < num_tokens; j++) {
            free(t[j]);
        }
        free(t);
        return NULL;
    }

    t[num_tokens] = NULL; // Null-terminate the array
    return t;
}
// int	main(void)
// {
// 	const char *str = "echo HOME$HOME$USER HOME";
// 	char **tokens = tokenizing(str);
// 	if (tokens)
// 	{
// 		int i = 0;
// 		while (tokens[i])
// 		{
// 			printf("[ %s ]   ", tokens[i]);
// 			i++;
// 		}
// 		free(tokens);
// 	}
// 	return (0);
// }
