/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:41:07 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 19:46:48 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_quotes(char *token, t_quote_state *state)
{
	if (!(state->found_quote) && (token[state->i] == '\"'
			|| token[state->i] == '\''))
	{
		state->found_quote = 1;
		state->quote_char = token[state->i];
		(state->i)++;
	}
	else if (state->found_quote && token[state->i] == state->quote_char)
	{
		state->found_quote = 0;
		(state->i)++;
	}
	else
	{
		state->result[state->j++] = token[state->i++];
	}
}

char	*remove_quotes(char *token)
{
	t_quote_state	state;
	int				len;

	len = ft_strlen(token);
	state.i = 0;
	state.j = 0;
	state.found_quote = 0;
	state.quote_char = '\0';
	state.result = (char *)malloc((len + 1) * sizeof(char));
	if (!state.result)
		return (NULL);
	while (token[state.i])
	{
		handle_quotes(token, &state);
	}
	state.result[state.j] = '\0';
	return (state.result);
}

void	quote_handing(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\''))
			tokens[i] = remove_quotes(tokens[i]);
		i++;
	}
}
