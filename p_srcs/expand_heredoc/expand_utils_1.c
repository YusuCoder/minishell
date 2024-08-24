/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:44:12 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 00:06:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_c_string_heredoc(char *token)
{
	int		i;
	int		x;
	int		size;
	char	*res;

	i = count_string_heredoc(token);
	i++;
	while (token[i] && !count_str(token[i]) && !is_exeption(token[i]))
	{
		if (token[i] == '\'' && token[i + 1] == '\"')
			break ;
		i++;
	}
	size = 0;
	while (token[i++])
		size++;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	x = 0;
	i = i - size - 1;
	while (x < size)
		res[x++] = token[i++];
	res[x] = '\0';
	return (res);
}

static char	*get_x_string_heredoc(char *token)
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
	res = (char *)malloc(sizeof(char) * (i + 1));
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

static char	*replace_token_heredoc(char *token, char *e_name)
{
	char	*x;
	char	*res;
	char	*final_res;
	char	*c;

	x = get_x_string_heredoc(token);
	c = get_c_string_heredoc(token);
	res = ft_strjoin(x, e_name);
	free(x);
	final_res = ft_strjoin(res, c);
	free(res);
	free(c);
	return (final_res);
}

char	*dollar_sign_heredoc(char *sign, char *token, char **env, t_data *data)
{
	char	*v_name;
	char	*e_name;
	char	*n_token;

	e_name = NULL;
	v_name = get_v_name(token);
	if (v_name[0] == '?')
		e_name = replace_question(v_name, data->exit_code);
	else
		e_name = get_e_name(v_name, env);
	if (e_name == NULL || e_name[0] == '\0')
	{
		n_token = remove_var(sign, v_name);
	}
	else
		n_token = replace_token_heredoc(sign, e_name);
	if (v_name)
		free(v_name);
	if (e_name != NULL)
		free(e_name);
	return (n_token);
}
