/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:08:53 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/21 21:18:11 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expansion_of_heredoc(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]))
			break ;
		i++;
	}
	return (i);
}

void	get_env_var_heredoc(char **token, char **env, t_data *data)
{
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	if (expansion_of_heredoc(*token) != -1)
	{
		dollar_ptr = ft_strchr(*token, '$');
		if (!dollar_ptr || dollar_ptr[1] == '\0' || count_str(dollar_ptr[1])
			|| is_exeption(dollar_ptr[1]))
		{
			return ;
		}
		x = expansion_of_heredoc(*token);
		expanded_token = dollar_sign_heredoc(*token, *token + x + 1, env, data);
		free(*token);
		*token = expanded_token;
	}
}

void	expand_heredoc(char **tokens, char **env, t_data *data)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		get_env_var_heredoc(&tokens[i], env, data);
		if (still_dollar_heredoc(tokens[i]))
			continue ;
		i++;
	}
}
