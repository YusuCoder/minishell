/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/23 23:52:27 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expansion_of_first_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]) && not_in_squote(token, i))
		{
			if (token[i + 1] == '\0' || token[i + 1] == '$'
				|| token[i + 1] == ' ' || is_exeption(token[i + 1]))
				return (-1);
			break ;
		}
		i++;
	}
	return (i);
}

static void	get_env_var(char **token, char **env, t_data *data)
{
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	dollar_ptr = ft_strchr(*token, '$');
	if (!dollar_ptr || dollar_ptr[1] == '\0' || dollar_ptr[1] == ' ')
		return ;
	if (dollar_ptr[1] == '"' || dollar_ptr[1] == '\'')
		memmove(dollar_ptr, dollar_ptr + 1, strlen(dollar_ptr));
	x = expansion_of_first_token(*token);
	if (x == -1)
		return ;
	expanded_token = dollar_sign(*token, *token + x + 1, env, data);
	free(*token);
	*token = expanded_token;
}

/*
	this function is responsible for expanding a certain token
	with ($) within the array
*/

void	expand(char **tokens, char **env, t_data *data)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		get_env_var(&tokens[i], env, data);
		if (still_dollar_sign_there(tokens[i]) && tokens[i][0] != '\0')
		{
			if (expansion_of_first_token(tokens[i]) == -1)
				break ;
			continue ;
		}
		i++;
	}
}
