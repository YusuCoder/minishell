
#include "../../includes/minishell.h"

// Handle export argument with no value
void	export_arg_no_value(char *arg, char ***env, int *exit_code)
{
	char	*name;

	name = arg;
	if (env_var_find(*env, name) == -1)
	{
		if (export_update_env(env, name, NULL, 0) != 0)
		{
			perror("export");
			*exit_code = 1;
		}
	}
}

// Handle export argument with value
void	export_arg_with_value(char *arg, char *equal_sign,
	char ***env, int *exit_code)
{
	char	*name;
	char	*value;

	name = my_strndup(arg, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (name && value)
	{
		if (export_update_env(env, name, value, 1) != 0)
		{
			perror("export");
			*exit_code = 1;
		}
	}
	else
	{
		write(2, "export: invalid argument\n", 25);
		*exit_code = 1;
	}
	free(name);
	free(value);
}

// Handle export command with arguments
void	export_with_args(char *arg, char ***env, int *exit_code)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		export_arg_with_value(arg, equal_sign, env, exit_code);
	else
		export_arg_no_value(arg, env, exit_code);
	if (*exit_code != 0)
		return ;
	*exit_code = 0;
}

// Handle export command with no arguments
void	export_no_args(char **env, int *exit_code)
{
	char	**sorted_env;
	int		i;
	char	*equal_sign;

	sorted_env = env_sort(env);
	if (!sorted_env)
	{
		perror("malloc");
		*exit_code = 1;
		return ;
	}
	i = 0;
	while (sorted_env[i])
	{
		equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(equal_sign - sorted_env[i]), sorted_env[i],
				equal_sign + 1);
		else
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
	*exit_code = 0;
}

// Main export command execution function
void	execute_export(char **args, char ***env, int *exit_code)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		export_no_args(*env, exit_code);
	else
	{
		while (args[i])
		{
			export_with_args(args[i], env, exit_code);
			if (*exit_code != 0)
				return ;
			i++;
		}
		*exit_code = 0;
	}
}
