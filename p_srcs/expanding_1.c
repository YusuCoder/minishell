/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:43:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/16 01:47:04 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_v_name(char *token)
{
	int		i;
	char	*v_name;
	int		start;
	int		length;

	i = 0;
	while (token[i] && (token[i] == '$' || token[i] == '{'))
	// Skiping initial characters that aren't part of a variable name
	{
		i++;
	}
	start = i;
	while (token[i] && !count_str(token[i]) && !is_exeption(token[i]))
	{
		i++; // Extracting characters until a non-variable character is found
	}
	length = i - start;
	v_name = (char *)malloc(sizeof(char) * (length + 1));
	// Allocateing space for the variable name, plus the null terminator
	if (!v_name)
		return (NULL);
	// Copy the variable name
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
	v_name_len = strlen(v_name);
	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = strchr(env[i], '=');
		if (equal_sign != NULL && (size_t)(equal_sign - env[i]) == v_name_len
			&& strncmp(v_name, env[i], v_name_len) == 0)
		{
			e_name = fill_e_name(equal_sign + 1, strlen(equal_sign + 1));
			break ;
		}
		i++;
	}
	if (e_name == NULL)
	{
		e_name = (char *)calloc(1, 1);
	}
	return (e_name);
}

// char	*get_e_name(char *v_name, char **env)
// {
// 	int		i;
// 	char	*e_name;
// 	size_t	v_name_len;
// 	char	*equal_sign;

// 	e_name = NULL;
// 	v_name_len = strlen(v_name);
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		equal_sign = strchr(env[i], '=');
// 		if (equal_sign != NULL && (size_t)(equal_sign - env[i]) == v_name_len
// 			&& strncmp(v_name, env[i], v_name_len) == 0)
// 		{
// 			e_name = fill_e_name(equal_sign + 1, strlen(equal_sign + 1));
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (e_name == NULL)
// 	{
// 		e_name = (char *)calloc(1, 1);
// 	}
// 	return (e_name);
// }

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
	if (e_name != NULL)
		free(e_name);
	final_res = ft_strjoin(res, c);
	free(res);
	free(c);
	return (final_res); // Corrected to return final_res
}

// char	*remove_var(char *token, char *v_name)
// {
// 	int		index;
// 	int		i;
// 	int		x;
// 	char	*n_token;

// 	index = 0;
// 	i = 0;
// 	x = 0;
// 	n_token = (char *)malloc((ft_strlen(token) - (ft_strlen(v_name))
// 				* sizeof(char)) + 21);
// 	if (!n_token)
// 		return (NULL);
// 	while (ft_strncmp(token + index, v_name, ft_strlen(v_name)) != 0)
// 		index++;
// 	while (token[i])
// 	{
// 		if (i == index - 1)
// 			i = i + ft_strlen(v_name) + 1;
// 		n_token[x] = token[i];
// 		i++;
// 		x++;
// 	}
// 	n_token[x] = '\0';
// 	return (n_token);
// }

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
	int		i;

	i = 0;
	e_name = NULL;
	v_name = get_v_name(token);
	if (ft_strcmp(v_name, "?") == 0)
		e_name = ft_itoa(*(data->exit_code));
	// else if (ft_strcmp(v_name, "_") == 0)
	// {
	// 	if (data->last_arg != NULL)
	// 	{
	// 		e_name = ft_strdup(data->last_arg);
	//echo $_ printing the last arg of previous command need to be fnished
	// 	}
	// 	else
	// 		e_name = NULL;
	// }
	else
		e_name = get_e_name(v_name, env);
	// while(data->tokens[i])
	// {
	// 	if (data->tokens[i + 1] == NULL)
	// 		data->last_arg = ft_strdup(data->tokens[i]);
	//setting last argument need to be finiished later
	// 	i++;
	// }
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
