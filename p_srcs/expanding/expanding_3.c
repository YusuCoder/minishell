/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:17:20 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 20:07:16 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	still_dollar_sign_there(char *token)
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

int	calculate_new_length(const char *var, const char *exit_code_str)
{
	int	i;
	int	new_length;

	i = 0;
	new_length = 0;
	while (var[i])
	{
		if (var[i] == '?')
			new_length += ft_strlen(exit_code_str);
		else
			new_length++;
		i++;
	}
	return (new_length);
}

void	build_result_string(const char *var, char *result,
		const char *exit_code_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '?')
		{
			strcpy(&result[j], exit_code_str);
			j += ft_strlen(exit_code_str);
		}
		else
		{
			result[j] = var[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
}

char	*replace_question(const char *var, int *exit_code)
{
	char	*exit_code_str;
	int		new_length;
	char	*result;

	exit_code_str = ft_itoa(*exit_code);
	if (!exit_code_str)
		return (NULL);
	new_length = calculate_new_length(var, exit_code_str);
	result = (char *)malloc((new_length + 1) * sizeof(char));
	if (!result)
	{
		free(exit_code_str);
		return (NULL);
	}
	build_result_string(var, result, exit_code_str);
	free(exit_code_str);
	return (result);
}

// char	*replace_question(const char *var, int *exit_code)
// {
// 	int		i;
// 	int		j;
// 	char	*exit_code_str;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	exit_code_str = ft_itoa(*exit_code);
// 	while (var[i])
// 	{
// 		if (var[i] == '?')
// 			j += ft_strlen(exit_code_str);
// 		else
// 			j++;
// 		i++;
// 	}
// 	result = (char *)malloc((j + 1) * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (var[i])
// 	{
// 		if (var[i] == '?')
// 		{
// 			strcpy(&result[j], exit_code_str);
// 			j += ft_strlen(exit_code_str);
// 		}
// 		else
// 			result[j++] = var[i];
// 		i++;
// 	}
// 	result[j] = '\0';
// 	free(exit_code_str);
// 	return (result);
// }
