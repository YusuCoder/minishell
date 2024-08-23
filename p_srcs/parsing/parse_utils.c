/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:25:39 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/23 21:45:08 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	this function checks if the begining of the given arguments
	is not this tokens if it is the function returns an error
*/
int	check_beginning_and_end(char **t, int i)
{
	if (ft_strncmp(t[i], ">", 1) == 0 || ft_strncmp(t[i], "<", 1) == 0)
		return (0);
	else if (t[i] && (ft_strncmp(t[0], "|", 1) == 0 || (i >= 1
				&& ft_strncmp(t[i], "|", 1) == 0)))
		return (0);
	return (1);
}
/*
	here im cheching for the tokens if the are correctly given
	e.g: cat < | wc -l OR echo helloWorld > > log.txt
*/

int	parse_redirs(char *current, char *next)
{
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "\n", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "\n", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	return (0);
}

static void	toggle_quote_state(char c, t_quote_state *quote_state)
{
	if (c == '\'' && !(quote_state->in_double_quote))
	{
		quote_state->in_single_quote = !(quote_state->in_single_quote);
		quote_state->squote++;
	}
	else if (c == '\"' && !(quote_state->in_single_quote))
	{
		quote_state->in_double_quote = !(quote_state->in_double_quote);
		quote_state->dquote++;
	}
}

static int	check_quote_balance(char *t)
{
	int				i;
	t_quote_state	quote_state;

	quote_state.dquote = 0;
	quote_state.in_double_quote = 0;
	quote_state.in_single_quote = 0;
	quote_state.squote = 0;
	i = 0;
	while (t[i])
	{
		toggle_quote_state(t[i], &quote_state);
		i++;
	}
	if (quote_state.squote % 2 != 0 || quote_state.dquote % 2 != 0)
		return (-1);
	return (0);
}

int	quotes_check(char *t)
{
	return (check_quote_balance(t));
}
