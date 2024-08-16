
#include "../../includes/minishell.h"

char	*env_value_get(char **env, const char *name)
{
	int		i;
	size_t	name_len;

	if (env == NULL || env[0] == NULL)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if ((ft_strncmp(env[i], name, name_len) == 0)
			&& (env[i][name_len] == '='))
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

void	env_value_delete(char **env, char *name)
{
	int	i;

	i = 0;
	while (i < env_len(env))
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(name);
			break ;
		}
		i++;
	}
}

void	env_value_change(char **env, const char *name, const char *value)
{
	int		i;
	size_t	name_len;
	char	*new_entry;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
		{
			free(env[i]);
			new_entry = ft_strjoin(name, "=");
			env[i] = ft_strjoin(new_entry, value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

int	env_value_change_pwd_oldpwd(char *prev_dir, char **env, int *exit_code)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (-1);
	}
	env_value_change(env, "OLDPWD", prev_dir);
	env_value_change(env, "PWD", curr_dir);
	return (0);
}
