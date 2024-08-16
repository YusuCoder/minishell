/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:41:07 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/14 18:07:56 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*remove_outer_quotes(char **token)
// {
// 	int		i;
// 	int		j;
// 	char	*new_token;

// 	i = 0;
// 	j = 0;
// 	new_token = (char *)malloc(ft_strlen(token) * sizeof(char) + 1);
// 	if (!new_token)
// 		return (NULL);
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '\"')
// 		{
// 			i++;
// 			continue;
// 		}
// 		new_token[j] = token[i];
// 		i++;
// 		j++;
// 	}
// 	new_token[j] = '\0';
// 	return (new_token);
// }

char	*remove_first_quote(char *token)
{
	int		i;
	int		j;
	int		check;
	char	*new_token;

	i = 0;
	j = 0;
	check = 0;
	new_token = (char *)malloc(sizeof(char) * ft_strlen(token) + 1);
	if (!new_token)
		return (NULL);
	while (token[i])
	{
		if (check == 0 && (token[i] == '\"' || token[i] == '\''))
		{
			i++;
			check = 1;
		}
		new_token[j] = token[i];
		i++;
		j++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	*remove_last_quote(char	*token)
{
	int	i;
	int	j;
	int	check;
	char	*new_token;

	i = ft_strlen(token) - 1;
	check = 0;
	new_token = (char *)malloc(ft_strlen(token) * sizeof(char) + 1);
	while (i > 0)
	{
		if (check == 0 && (token[i] == '\"' || token[i] == '\''))
			check = i;
		i--;
	}
	j = 0;
	while (i < (int)(ft_strlen(token)))
	{
		if (i == check)
			i++;
		new_token[j] = token[i];
		j++;
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

void	quote_handing(char **tokens)
{
	int		i;
	char	*temp;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\''))
		{
			temp = tokens[i];
			tokens[i] = remove_first_quote(tokens[i]);
			free(temp);
			temp = NULL;
			temp = tokens[i];
			tokens[i] = remove_last_quote(tokens[i]);
			free(temp);
		}
		i++;
	}
}
