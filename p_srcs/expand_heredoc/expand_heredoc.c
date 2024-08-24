/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:08:53 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 00:20:29 by ryusupov         ###   ########.fr       */
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

	while (1)
	{
		if (expansion_of_heredoc(*token) != -1)
		{
			dollar_ptr = ft_strchr(*token, '$');
			if (!dollar_ptr || dollar_ptr[1] == '\0'
				|| count_str(dollar_ptr[1])
				|| is_exeption(dollar_ptr[1]))
				break ;
			x = expansion_of_heredoc(*token);
			expanded_token = dollar_sign_heredoc(*token, *token + x + 1, env,
					data);
			free(*token);
			*token = expanded_token;
			if (!still_dollar_heredoc(*token))
				break ;
		}
		else
			break ;
	}
}

void	expand_heredoc(char **line, char **env, t_data *data)
{
	if (*line)
	{
		get_env_var_heredoc(line, env, data);
	}
}
