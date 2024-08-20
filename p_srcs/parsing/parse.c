/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:27:31 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 20:21:35 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	This function counts number of single or double quotes
	if number of any of them is odd that means that quote is not closed
*/

// int	quotes_check(char *t)
// {
// 	int	i;
// 	int	squote;
// 	int	dquote;
// 	int	in_single_quote;
// 	int	in_double_quote;

// 	i = 0;
// 	squote = 0;
// 	dquote = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	while (t[i])
// 	{
// 		if (t[i] == '\'' && !in_double_quote)
// 		{
// 			if (in_single_quote)
// 				in_single_quote = 0;
// 			else
// 				in_single_quote = 1;
// 			squote++;
// 		}
// 		if (t[i] == '\"' && !in_single_quote)
// 		{
// 			if (in_double_quote)
// 				in_double_quote = 0;
// 			else
// 				in_double_quote = 1;
// 			dquote++;
// 		}
// 		i++;
// 	}
// 	if (squote % 2 != 0 || dquote % 2 != 0)
// 		return (-1);
// 	return (0);
// }

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
