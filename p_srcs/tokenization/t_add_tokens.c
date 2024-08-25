/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_add_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:19 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 22:32:19 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
It iterates through each character of the input string str.
If the character is a word it increments the index i and
continues to the next character.
Otherwise,
it calculates the length of the token starting from the
current index i.
If the token has a single character it adds the length of the word
plus one for '/0'.
Otherwise,
it iterates through the characters until it finds the end
of the token.
Then allocating the memory for the tokens.
at the end copying the token to the allocated memory
*/
int	handle_variable_or_quoted_string(const char *str)
{
	char	quote;
	int		len;

	len = 1;
	if (str[len] == '"' || str[len] == '\'')
	{
		quote = str[len];
		len++;
		while (str[len] && str[len] != quote)
		{
			len++;
		}
		if (str[len] == quote)
			len++;
	}
	else
	{
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
	}
	return (len);
}

int	get_special_char_length(const char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
			return (2);
		else
			return (1);
	}
	return (0);
}

int	get_quoted_or_regular_length(const char *str, int i)
{
	int		len;
	int		in_quotes;
	char	quote_char;

	len = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (str[i + len] && (in_quotes || (str[i + len] != ' ' && str[i
					+ len] != '\t' && str[i + len] != '|' && str[i
					+ len] != '>' && str[i + len] != '<')))
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
	return (len);
}

int	get_token_length(const char *str, int i)
{
	int	len;

	len = get_special_char_length(str, i);
	if (len > 0)
		return (len);
	return (get_quoted_or_regular_length(str, i));
}

int	take_tokens(char **token, const char *str, int i)
{
	int	counter;
	int	len;

	counter = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break ;
		len = get_token_length(str, i);
		token[counter] = (char *)malloc((len + 1) * sizeof(char));
		if (!token[counter])
		{
			free_array(token);
			return (-1);
		}
		ft_memcpy(token[counter], &str[i], len);
		token[counter][len] = '\0';
		counter++;
		i += len;
	}
	return (counter);
}
