/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:44:12 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 00:15:01 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollar_sign_heredoc(char *sign, char *token, char **env, t_data *data)
{
	char	*v_name;
	char	*e_name;
	char	*n_token;

	e_name = NULL;
	v_name = get_v_name(token);
	if (v_name[0] ==  '?')
		e_name = replace_question(v_name, data->exit_code);
	else
		e_name = get_e_name(v_name, env);
	if (e_name == NULL || e_name[0] == '\0')
	{
		n_token = remove_var(sign, v_name);
	}
	else
		n_token = replace_token(sign, e_name);
	if (v_name)
		free(v_name);
	return (n_token);
}

int	additional_dollar_sign(char *token)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (token[i])
	{
		if (token[i] == '$')
			check = check + not_in_squote(token, i);
		i++;
	}
	if (check > 0)
		return (1);
	else
		return (0);
}

int	start_expansion(char *token)
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

char	*get_x_string_heredoc(char	*token)
{
	int		i;
	char	*res;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			break ;
		i++;
	}
	res = (char *)malloc(sizeof(char) * (i  + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			break ;
		res[i] = token[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	expand_heredoc(char **tokens, char **env, t_data *data)
{
	int		i;
	int		x;
	char	*expanded_token;

	i = 0;
	while (tokens[i])
	{
		if (start_expansion(tokens[i]) != -1)
		{
			x = start_expansion(tokens[i]);
			expanded_token = dollar_sign_heredoc(tokens[i], tokens[i] + x + 1, env,
					data);
			free(tokens[i]);
			tokens[i] = expanded_token;
			// free(expanded_token);
		}
		if (additional_dollar_sign(tokens[i]))
			continue ;
		i++;
	}
}
