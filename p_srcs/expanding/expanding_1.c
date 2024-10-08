/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:43:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 22:09:23 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_v_name(char *token)
{
	int		i;
	char	*v_name;
	int		start;
	int		length;

	i = 0;
	while (token[i] && (token[i] == '$' || token[i] == '{'))
	{
		i++;
	}
	start = i;
	while (token[i] && !count_str(token[i]) && !is_exeption(token[i]))
	{
		i++;
	}
	length = i - start;
	v_name = (char *)malloc(sizeof(char) * (length + 1));
	if (!v_name)
		return (NULL);
	strncpy(v_name, token + start, length);
	v_name[length] = '\0';
	return (v_name);
}

char	*get_e_name(char *v_name, char **env)
{
	int		i;
	char	*e_name;
	size_t	v_name_len;
	char	*equal_sign;

	e_name = NULL;
	v_name_len = ft_strlen(v_name);
	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL && (size_t)(equal_sign - env[i]) == v_name_len
			&& ft_strncmp(v_name, env[i], v_name_len) == 0)
		{
			e_name = fill_e_name(equal_sign + 1, ft_strlen(equal_sign + 1));
			break ;
		}
		i++;
	}
	if (e_name == NULL)
		e_name = (char *)ft_calloc(1, 1);
	return (e_name);
}

char	*replace_token(char *token, char *e_name)
{
	char	*x;
	char	*res;
	char	*final_res;
	char	*c;

	x = get_x_string(token);
	c = get_c_string(token);
	res = ft_strjoin(x, e_name);
	free(x);
	final_res = ft_strjoin(res, c);
	free(res);
	free(c);
	return (final_res);
}

char	*remove_var(char *token, char *v_name)
{
	int		index;
	int		i;
	int		x;
	char	*n_token;

	index = 0;
	i = 0;
	x = 0;
	n_token = (char *)malloc(ft_strlen(token) - ft_strlen(v_name) + 1);
	if (!n_token)
		return (NULL);
	while (ft_strncmp(token + index, v_name, ft_strlen(v_name)) != 0)
		index++;
	while (token[i])
	{
		if (i == index - 1)
			i += ft_strlen(v_name) + 1;
		if (token[i])
			n_token[x++] = token[i++];
	}
	n_token[x] = '\0';
	return (n_token);
}

char	*dollar_sign(char *sign, char *token, char **env, t_data *data)
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
		n_token = replace_token(sign, e_name);
	if (v_name)
		free(v_name);
	if (e_name != NULL)
		free(e_name);
	return (n_token);
}
