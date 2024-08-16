/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_add_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:19 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/16 13:46:25 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*this funciton checks if there is any additional character after
the given token. And returns the index of the first cahracter after the token*/
// static int	check_for_additional_token(const char *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[i] && count_tokens(token[i]) != 1 && !count_str(token[i]))
// 	{
// 		i++;
// 	}
// 	return (i);
// }
/*this function copies the the tokens from input to allocated memory*/
// static int	copy_tokens(char *where, const char *from, int	len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		where[i] = from[i];
// 		i++;
// 	}
// 	where[i] = '\0';
// 	return (len);

// }
/*allocating the memory to keep the array of the tokens*/
int	alloc_tokens(char **token, int counter, int len)
{
	token[counter] = (char *)malloc((len + 1) * sizeof(char));
	if (!token[counter])
	{
		fprintf(stderr, "Memory allocation failed for token[%d]\n", counter);
		exit(EXIT_FAILURE);
	}
	return (0);
}
/*
It iterates through each character of the input string str.
If the character is a word it increments the index i and continues to the next character.
Otherwise,
	it calculates the length of the token starting from the current index i.
If the token has a single character it adds the length of the word plus one for '/0'.
Otherwise,
	it iterates through the characters until it finds the end of the token.
Then allocating the memory for the tokens.
at the end copying the token to the allocated memory
*/
int	handle_variable_or_quoted_string(const char *str)
{
	char	quote;

	int len = 1; // Start at 1 to account for the '$' itself
	if (str[len] == '"' || str[len] == '\'') // Quoted string following $
	{
		quote = str[len];
		len++; // Include the opening quote
		while (str[len] && str[len] != quote)
		{
			len++;
		}
		if (str[len] == quote)
			len++; // Include the closing quote
	}
	else
	{
		while (str[len] && (isalnum(str[len]) || str[len] == '_'))
		{
			len++;
		}
	}
	return (len);
}

int	take_tokens(char **token, const char *str, int i)
{
	int		counter;
	int		j;
	int		len;
	int		in_quotes;
	char	quote_char;

	counter = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break ;
		len = 0;
		in_quotes = 0;
		quote_char = '\0';
		while (str[i + len] && (in_quotes || (str[i + len] != ' ' && str[i
					+ len] != '\t')))
		{
			if ((str[i + len] == '\'' || str[i + len] == '\"') && !in_quotes)
			{
				in_quotes = 1;
				quote_char = str[i + len];
			}
			else if (str[i + len] == quote_char && in_quotes)
				in_quotes = 0;
			len++;
		}
		token[counter] = (char *)malloc((len + 1) * sizeof(char));
		if (!token[counter])
		{
			j = 0;
			while (j < counter)
			{
				free(token[j]);
				j++;
			}
			return (-1);
		}
		ft_memcpy(token[counter], &str[i], len);
		token[counter][len] = '\0';
		counter++;
		i += len;
	}
	return (counter);
}
