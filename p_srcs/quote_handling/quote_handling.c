/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:41:07 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 21:14:14 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_quotes(char *token, t_quote_state *state)
{
	while (token[state->i])
	{
		if (!state->found_quote && (token[state->i] == '\"'
				|| token[state->i] == '\''))
		{
			state->found_quote = 1;
			state->quote_char = token[state->i];
			state->i++;
		}
		else if (state->found_quote && token[state->i] == state->quote_char)
		{
			state->found_quote = 0;
			state->quote_char = '\0';
			state->i++;
		}
		else
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
	handle_quotes(token, &state);
	state.result[state.j] = '\0';
	return (state.result);
}

void	quote_handing(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	int		i;
	char	*new_cmd;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		i = -1;
		while (current_cmd->cmd_array[++i])
		{
			if (ft_strchr(current_cmd->cmd_array[i], '\"')
				|| ft_strchr(current_cmd->cmd_array[i], '\''))
			{
				new_cmd = remove_quotes(current_cmd->cmd_array[i]);
				if (new_cmd)
				{
					free(current_cmd->cmd_array[i]);
					current_cmd->cmd_array[i] = new_cmd;
				}
				else
					printf("Error.\n");
			}
		}
		current_cmd = current_cmd->next;
	}
}
