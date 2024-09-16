/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:27:31 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/26 16:52:13 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	This function counts number of single or double quotes
	if number of any of them is odd that means that quote is not closed
*/

int	check_quotes(char *token, t_data *data)
{
	if (quotes_check(token) < 0)
	{
		ft_perror_parsing("minishell: ", "syntax error unclosed quotes ", token,
			data->exit_code);
		return (-1);
	}
	return (0);
}

int	check_pipes_and_redirs(char **t, int i, t_data *data)
{
	if (t[i + 1] && (((ft_strncmp(t[i], "|", 1) == 0) && (ft_strncmp
					(t[i + 1], "|", 1) == 0)) || parse_redirs
			(t[i], t[i + 1]) < 0))
	{
		ft_perror_parsing("minishell: ", "syntax error near unexpected token ",
			t[i + 1], data->exit_code);
		return (-1);
	}
	return (0);
}

int	check_beginning_and_end_syntax(char **t, int last_index, t_data *data)
{
	if (!check_beginning_and_end(t, last_index))
	{
		ft_perror_parsing("minishell: ", "syntax error near unexpected token ",
			t[last_index], data->exit_code);
		return (-1);
	}
	return (0);
}

int	parse(char **t, t_data *data)
{
	int	i;

	if (t == NULL)
		return (1);
	i = 0;
	if (t[i] == NULL)
		return (1);
	while (t[i])
	{
		if (check_quotes(t[i], data) < 0)
			return (1);
		if (check_pipes_and_redirs(t, i, data) < 0)
			return (1);
		i++;
	}
	if (check_beginning_and_end_syntax(t, i - 1, data) < 0)
		return (1);
	return (0);
}
