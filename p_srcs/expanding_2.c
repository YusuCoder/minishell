/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:22:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/16 01:59:33 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	count_string(char	*token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]) && not_in_squote(token, i))
			break;
		i++;
	}
	return (i);
}

// char	*fill_e_name(char *line, int i)
// {
// 	int		x;
// 	char	*e_name;

// 	x = 0;
// 	while (line[i + x])
// 		x++;
// 	e_name = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!e_name)
// 		return (NULL);
// 	while (line[i + x])
// 	{
// 		e_name[i] = line[i + x];
// 		x++;
// 	}
// 	e_name[x] = '\0';
// 	return (e_name);
// }

char *fill_e_name(char *line, int length)
{
    char *e_name = (char *)malloc(sizeof(char) * (length + 1)); // Allocate memory for the substring + null terminator
    if (!e_name)
        return (NULL);

    for (int i = 0; i < length; i++) // Copy the substring
    {
        e_name[i] = line[i];
    }
    e_name[length] = '\0'; // Null-terminate the string

    return e_name;
}


char	*get_x_string(char	*token)
{
	int		i;
	char	*res;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && not_in_squote(token, i))
			break ;
		i++;
	}
	res = (char *)malloc(sizeof(char) * (i  + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && not_in_squote(token, i))
			break ;
		res[i] = token[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


char	*get_c_string(char *token)
{
	int	i;
	int	x;
	int	size;
	char *res;

	i = count_string(token);
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
