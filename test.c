#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// int	alloc_tokens(char **token, int counter, int len)
// {
// 	token[counter] = (char *)malloc((len + 1) * sizeof(char));
// 	if (!token[counter])
// 	{
// 		fprintf(stderr, "Memory allocation failed for token[%d]\n", counter);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

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


// int	take_tokens(char **token, const char *str, int i)
// {
// 	int		counter;
// 	int		len;
// 	int		in_quotes;
// 	char	quote_char;

// 	counter = 0;
// 	while (str[i])
// 	{
// 		while (str[i] == ' ' || str[i] == '\t')
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		len = 0;
// 		in_quotes = 0;
// 		quote_char = '\0';
// 		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
// 		{
// 			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
// 					+ 1] == '<'))
// 				len = 2;
// 			else
// 				len = 1;
// 		}
// 		else
// 		{
// 			while (str[i + len] && (in_quotes || (str[i + len] != ' ' && str[i
// 						+ len] != '\t' && str[i + len] != '|' && str[i
// 						+ len] != '>' && str[i + len] != '<')))
// 			{
// 				if ((str[i + len] == '\'' || str[i + len] == '\"')
// 						&& !in_quotes)
// 				{
// 					in_quotes = 1;
// 					quote_char = str[i + len];
// 				}
// 				else if (str[i + len] == quote_char && in_quotes)
// 					in_quotes = 0;
// 				len++;
// 			}
// 		}
// 		token[counter] = (char *)malloc((len + 1) * sizeof(char));
// 		if (!token[counter])
// 		{
// 			free_array(token);
// 			return (-1);
// 		}
// 		ft_memcpy(token[counter], &str[i], len);
// 		token[counter][len] = '\0';
// 		counter++;
// 		i += len;
// 	}
// 	return (counter);
// }



// int	take_tokens(char **token, const char *str, int i)
// {
// 	int		counter;
// 	// int		in_quotes;
// 	char	quote_char;

// 	counter = 0;
// 	int j, len;
// 	while (str[i])
// 	{
// 		while (str[i] == ' ' || str[i] == '\t')
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		len = 0;
// 		// in_quotes = 0;
// 		quote_char = '\0';
// 		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
// 		{
// 			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
// 					+ 1] == '<'))
// 				len = 2;
// 			else
// 				len = 1;
// 		}
// 		else
// 		{
// 			if (str[i] == '\'' || str[i] == '\"')
// 			{
// 				// in_quotes = 1;
// 				quote_char = str[i];
// 				len++;
// 				while (str[i + len])
// 				{
// 					len++;
// 					if (str[i + len - 1] == quote_char)
// 						break ;
// 				}
// 			}
// 			else
// 			{
// 				while (str[i + len] && (str[i + len] != ' ' && str[i
// 						+ len] != '\t' && str[i + len] != '|' && str[i
// 						+ len] != '>' && str[i + len] != '<' && str[i
// 						+ len] != '\'' && str[i + len] != '\"'))
// 					len++;
// 			}
// 		}
// 		token[counter] = (char *)malloc((len + 1) * sizeof(char));
// 		if (!token[counter])
// 		{
// 			for (j = 0; j < counter; j++)
// 				free(token[j]);
// 			return (-1);
// 		}
// 		strncpy(token[counter], &str[i], len);
// 		token[counter][len] = '\0';
// 		counter++;
// 		i += len;
// 	}
// 	return (counter);
// }



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
// 		if (count_tokens(str[i]) == 2) // Quoted token
// 		{
// 			i += matching_quotes(str + i);
// 			counter++;
// 		}
// 		else
// 		{
// 			while (str[i] && !count_str(str[i]) && count_tokens(str[i]) == 0)
// 				i++;
// 			counter++;
// 		}
// 		if (count_str(str[i]))
// 			i++;
// 	}
// 	return (counter);
// }

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


// int	not_in_squote(char *token, int i)
// {
// 	int	x;
// 	int	left;
// 	int	right;

// 	x = i;
// 	left = 0;
// 	right = 0;
// 	while (i >= 0)
// 	{
// 		if (token[i] == '\'')
// 		{
// 			if (token[i - 1] != '\"')
// 				left = 1;
// 		}
// 		i--;
// 	}
// 	while (token[x])
// 	{
// 		if (token[x] == '\'')
// 		{
// 			if (token[x + 1] != '\"')
// 				right = 1;
// 		}
// 		x++;
// 	}
// 	if (right && left)
// 		return (0);
// 	return (1);
// }





// int	parse(char **t, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (t[i] == NULL)
// 		return (1);
// 	while (t[i])
// 	{
// 		if (quotes_check(t[i]) < 0)
// 		{
// 			ft_perror_parsing("minishell: ", "syntax error unclosed quotes ",
//					t[i], data->exit_code);
// 			return (1);
// 		}
// 		if (t[i + 1] && (((strncmp(t[i], "|", 1) == 0) && (strncmp(t[i + 1],
// 							"|", 1) == 0)) || parse_redirs(t[i], t[i + 1]) < 0))
// 		{
// 			ft_perror_parsing("minishell: ",
//					"syntax error near unexpected token ", t[i + 1],
//					data->exit_code);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (!check_beginning_and_end(t, i - 1))
//     {
//         ft_perror_parsing("minishell: ",
//		"syntax error near unexpected token ", t[0], data->exit_code);
// 		return (1);
//     }
// 	return (0);
// }







// char	*remove_outer_quotes(char **token)
// {
// 	int		i;
// 	int		j;
// 	char	*new_token;
//     char    *quote_type;

// 	i = 0;
// 	j = 0;
// 	new_token = (char *)malloc(ft_strlen(token) * sizeof(char) + 1);
// 	if (!new_token)
// 		return (NULL);
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '\"')
// 		{
//             quote_type = token[i];
// 			i++;
// 			continue;
// 		}
// 		new_token[j] = token[i];
// 		i++;
// 		j++;
// 	}
// 	new_token[j] = '\0';
// 	return (new_token);
// }

// char *remove_first_quote(char *token) {
//     int i = 0;
//     int j = 0;
//     int found_quote = 0;
//     int len = ft_strlen(token);
//     char *new_token = (char *)malloc((len + 1) * sizeof(char));

//     if (!new_token)
//         return NULL;

//     while (token[i]) {
//         if (!found_quote && (token[i] == '\"' || token[i] == '\'')) {
//             found_quote = 1;
//             i++;
//             continue; // Skip the first quote
//         }
//         new_token[j++] = token[i++];
//     }
//     new_token[j] = '\0';
//     return new_token;
// }

// char *remove_last_quote(const char *token) {
//     int i = ft_strlen(token) - 1;
//     int j;
//     int found_quote = 0;
//     char *new_token;

//     while (i >= 0) {
//         if (!found_quote && (token[i] == '\"' || token[i] == '\'')) {
//             found_quote = 1;
//             break;
//         }
//         i--;
//     }
//     new_token = (char *)malloc((i + 1) * sizeof(char));
//     if (!new_token)
//         return NULL;
//     j = 0;
//     while (j < i) {
//         new_token[j] = token[j];
//         j++;
//     }
//     new_token[j] = '\0';
//     return new_token;
// }

// void quote_handing(char **tokens) {
//     int i = 0;
//     char *temp;

//     while (tokens[i]) {
//         if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\'')) {
//             temp = tokens[i];
//             // printf("original token: %s\n", tokens[i]);
//             tokens[i] = remove_first_quote(tokens[i]);
//             // printf("after removing firest quote %s\n", tokens[i]);
//             free(temp);
//             temp = tokens[i];
//             tokens[i] = remove_last_quote(tokens[i]);
//             // printf("after removing last quote %s\n", tokens[i]);
//             free(temp);
//         }
//         i++;
//     }
// }





// char	*remove_quotes(char *token)
// {
// 	int		i;
//     int     j;
// 	int		found_quote;
// 	char	quote_char;
// 	int		len;
// 	char	*new_token;

// 	i = 0;
//     j = 0;
// 	found_quote = 0;
// 	quote_char = '\0';
// 	len = ft_strlen(token);
// 	new_token = (char *)malloc((len + 1) * sizeof(char));
// 	if (!new_token)
// 		return (NULL);
// 	while (token[i])
// 	{
// 		if (!found_quote && (token[i] == '\"' || token[i] == '\''))
// 		{
// 			found_quote = 1;
// 			quote_char = token[i];
// 			i++;
// 			continue ;
// 		}
// 		if (found_quote && token[i] == quote_char)
// 		{
// 			i++;
// 			found_quote = 0;
// 			continue ;
// 		}
// 		new_token[j++] = token[i++];
// 	}
// 	new_token[j] = '\0';
// 	return (new_token);
// }
