/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:39:28 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/09 18:55:26 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to execute the "unset" command
void	execute_unset(char **args, char ***env, int *exit_code)
{
	int		i;
	int		j;

	i = 0;
	if (args[1] == NULL)
		return ;
	while (args[++i])
	{
		j = -1;
		while ((*env)[++j])
		{
			if (ft_strncmp((*env)[j], args[i], strlen(args[i])) == 0)
			{
				if (env_var_remove(env, j) != 0)
				{
					write(2, "unset: memory allocation error\n", 31);
					*exit_code = 1;
					return ;
				}
				break ;
			}
		}
	}
	*exit_code = 0;
}
