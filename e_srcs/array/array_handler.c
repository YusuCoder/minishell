/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:45:53 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/18 17:05:15 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Length of the 2D array
int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

// Copy 2D array and allocate new memory for it
char	**array_copy(char **array)
{
	char	**new_array;
	int		len_array;
	int		i;

	len_array = array_len(array);
	new_array = (char **)malloc((len_array + 1) * sizeof(char *));
	if (!new_array)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < len_array)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			while (i > 0)
				free(new_array[--i]);
			free(new_array);
			return (perror("malloc"), NULL);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
