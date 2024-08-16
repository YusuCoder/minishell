/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:18:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 12:18:44 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_create_new(void)
{
	char	**new_env;
	char	path_pwd[PATH_MAX];
	// char	*path_minishell;

	new_env = (char **)malloc((5) * sizeof(char *));
	if (!new_env)
		return (NULL);
	if (getcwd(path_pwd, sizeof(path_pwd)) == NULL)
		return (NULL);
	new_env[0] = ft_strjoin("PWD=", path_pwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strjoin("_=", path_pwd); //<-- !!! Here must be path_minishell !!!
	new_env[3] = ft_strdup("OLDPWD");
	new_env[4] = NULL;
	return (new_env);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	**env_set(char **env)
{
	char	**new_env;
	int		len_env;
	int		i;

	len_env = env_len(env);
	new_env = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len_env)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	env_increase_shlvl(char ***env)
{
	char	*name;
	char	*value;
	char	*new_var;
	int		index;

	name = "SHLVL";
	index = env_var_find(*env, name);
	if (index == -1)
	{
		new_var = env_var_create(name, "1");
		env_var_add(env, new_var);
	}
	else
	{
		value = env_value_get(*env, name);
		value = ft_itoa(ft_atoi(value) + 1);
		free((*env)[index]);
		(*env)[index] = env_var_create(name, value);
		free(value);
	}
}

void	env_reset_oldpwd(char ***env)
{
	char	*name;
	char	*new_var;
	int		index;

	name = "OLDPWD";
	new_var = NULL;
	index = env_var_find_no_value(*env, name);
	if (index == -1)
	{
		new_var = ft_strdup(name);
		env_var_add(env, new_var);
	}
	else
	{
		free((*env)[index]);
		(*env)[index] = ft_strdup(name);
	}
}
