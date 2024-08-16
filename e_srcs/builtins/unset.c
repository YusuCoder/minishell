/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:39:28 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/14 12:34:58 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to execute the "unset" command
int	execute_unset(char **args, char ***env, int *exit_code)
{
	int		i;
	int		j;

	i = 0;
	if (array_len(args) == 1 || env == NULL || env[0] == NULL)
		return (1);
	while (args[++i])
	{
		j = -1;
		while ((*env)[++j])
		{
			if (ft_strncmp((*env)[j], args[i], strlen(args[i])) == 0)
			{
				if (env_var_remove(env, j) == -1)
				{
					perror("malloc");
					*exit_code = 1;
					return (-1);
				}
				break ;
			}
		}
	}
	*exit_code = 0;
	return (0);
}
