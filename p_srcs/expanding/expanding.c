/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 20:07:07 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_left_quote(char *token, int i)
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

int	check_right_quote(char *token, int i)
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

int	is_exeption(char c)
{
	if (c == '/' || c == '=' || c == '\"' || c == '$' || c == '\\')
		return (1);
	if (c == '\'' || c == '+' || c == '-')
		return (1);
	return (0);
}

int	expansion_of_first_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]) && not_in_squote(token, i))
			break ;
		i++;
	}
	return (i);
}

// char *skip_dollar(char *token)
// {
//     int i, j;
//     int len;
//     char *new_token;

//     if (!token)
//         return (NULL);

//     len = strlen(token);
//     new_token = (char *)malloc(len + 1);
//     if (!new_token)
//         return (NULL);
//     i = 0;
//     j = 0;
//     while (token[i])
//     {
//         if (token[i] != '$')
//         {
//             new_token[j] = token[i];
//             j++;
//         }
//         i++;
//     }
//     new_token[j] = '\0';

//     return (new_token);
// }
/*
	this function is responsible for expanding a certain token
	with ($) within the array
*/
void	expand(char **tokens, char **env, t_data *data)
{
	int		i;
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	i = 0;
	while (tokens[i])
	{
		if (expansion_of_first_token(tokens[i]) != -1)
		{
			dollar_ptr = ft_strchr(tokens[i], '$');
			if (!dollar_ptr || dollar_ptr[1] == '\0' || count_str(dollar_ptr[1])
				|| is_exeption(dollar_ptr[1]))
			{
				i++;
				continue ;
			}
			x = expansion_of_first_token(tokens[i]);
			expanded_token = dollar_sign(tokens[i], tokens[i] + x + 1, env,
					data);
			free(tokens[i]);
			tokens[i] = expanded_token;
			// free(expanded_token);
		}
		if (still_dollar_sign_there(tokens[i]))
			continue ;
		i++;
	}
}
