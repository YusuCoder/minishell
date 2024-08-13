/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:43:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/13 21:47:00 by ryusupov         ###   ########.fr       */
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
	// Skip initial characters that aren't part of a variable name
	while (token[i] && (token[i] == '$' || token[i] == '{'))
	{
		i++;
	}
	start = i;
	// Extract characters until a non-variable character is found
	while (token[i] && !count_str(token[i]) && !is_exeption(token[i]))
	{
		i++;
	}
	length = i - start;
	// Allocate space for the variable name, plus the null terminator
	v_name = (char *)malloc(sizeof(char) * (length + 1));
	if (!v_name)
		return (NULL);
	// Copy the variable name
	strncpy(v_name, token + start, length);
	v_name[length] = '\0';
	return (v_name);
}

// #include <stdarg.h>
// void debug_print(const char *format, ...) {
//     va_list args;
//     va_start(args, format);
//     vprintf(format, args);
//     va_end(args);
// }

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
	// if (e_name != NULL)
	//     free(e_name);
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
	n_token = (char *)malloc((ft_strlen(token) - (ft_strlen(v_name))
				* sizeof(char)) + 21);
	if (!n_token)
		return (NULL);
	while (ft_strncmp(token + index, v_name, ft_strlen(v_name)) != 0)
		index++;
	while (token[i])
	{
		if (i == index - 1)
			i = i + ft_strlen(v_name) + 1;
		n_token[x] = token[i];
		i++;
		x++;
	}
	n_token[x] = '\0';
	return (n_token);
}

char	*dollar_sign(char *sign, char *token, char **env, int exit_code)
{
	char	*v_name;
	char	*e_name;
	char	*n_token;

	e_name = NULL;
	v_name = get_v_name(token);
	if (ft_strcmp(v_name, "?") == 0)
		e_name = ft_itoa(exit_code);
	else
		e_name = get_e_name(v_name, env);
	if (e_name[0] == '\0')
	{
		// printf("HELLO\n");
		n_token = remove_var(sign, v_name);
	}
	else
		n_token = replace_token(sign, e_name);
	if (v_name)
		free(v_name);
	return (n_token);
}
