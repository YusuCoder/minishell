
#include "../../includes/minishell.h"

// Set environment variable
int	export_update_env(char ***env, const char *name, const char *value,
	int overwrite)
{
	int		i;
	char	*new_env_var;

	i = env_var_find(*env, name);
	new_env_var = env_var_create(name, value);
	if (!new_env_var)
		return (-1);
	if (i != -1)
	{
		if (overwrite)
		{
			free((*env)[i]);
			(*env)[i] = new_env_var;
		}
		else
			free(new_env_var);
		return (0);
	}
	return (env_var_add(env, new_env_var));
}
