/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/21 21:41:32 by ryusupov         ###   ########.fr       */
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
			break ;
		i++;
	}
	return (i);
}

static void	get_env_var(char **token, char **env, t_data *data)
{
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	if (expansion_of_first_token(*token) != -1)
	{
		dollar_ptr = ft_strchr(*token, '$');
		if (!dollar_ptr || dollar_ptr[1] == '\0' || count_str(dollar_ptr[1])
			|| is_exeption(dollar_ptr[1]))
		{
			return ;
		}
		x = expansion_of_first_token(*token);
		expanded_token = dollar_sign(*token, *token + x + 1, env, data);
		free(*token);
		*token = expanded_token;
	}
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
		if (still_dollar_sign_there(tokens[i]))
			continue ;
		i++;
	}
}
