
#include "./includes/minishell.h"

char	*read_line(char *line)
{
	char	*cwd;
	char	*home;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (line)
	{
		free(line);
		line = NULL;
	}
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		cwd += ft_strlen(home);
		if (*cwd == '/')
			cwd++;
	}
	printf(RED"~/%s $\n"RESET, cwd);
	line = readline(GREEN">>> "RESET);
	if (line && *line != '\0')
		add_history(line);
	return (line);
}

void	set_data(t_data *data, char **envp, int	*exit_code)
{
	data->exit_code = exit_code;
	data->cmd_list = NULL;
	data->cmd_num = 0;
	data->tokens = NULL;
	if (envp[0] == NULL)
	{
		data->env = env_create_new();
		if (data->env == NULL)
		{
			*exit_code = 1;
			exit(*exit_code);
		}
	}
	else
	{
		data->env = env_set(envp);
		if (data->env == NULL)
		{
			*exit_code = 1;
			exit(*exit_code);
		}
		env_reset_oldpwd(&data->env);
		env_increase_shlvl(&data->env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	int		exit_code;

	(void)argv;
	(void)argc;
	line = NULL;
	exit_code = 0;
	// _init_terminal(&gl_command);
	set_data(&data, envp, &exit_code);
	while(1)
	{
		line = read_line(line);
		if (!line)
			break ;
		data.tokens = tokenizing(line);
		int i = 0;
		while (data.tokens && data.tokens[i] != NULL)
		{
			// printf("[ %s ]\n", t.tokens[i]);
			if (!parse(data.tokens) && data.tokens)
				break ;
			i++;
		}
		i = 0;
		if (data.tokens != NULL)
		{
			expand(data.tokens, data.env, &data);
			quote_handing(data.tokens);
 			cmd_list_create(data.tokens, &data);
			execute(&data);
		}
		// if (!t.tokens)
		// 	return (0);
	}
	return (exit_code);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*line;
// 	t_command	t;
// 	int			exit_code;

// 	(void)argv;
// 	(void)argc;
// 	line = NULL;
// 	exit_code = 0;
// 	_init_terminal(&gl_command, envp);
// 	t.envp = env_set(envp);
// 	env_value_delete(t.envp, "OLDPWD");
// 	// print_envp(t.envp);
// 	while(1)
// 	{
// 		line = read_line(line);
// 		if (!line)
// 			break ;
// 		t.tokens = tokenizing(line);
// 		int i = 0;
// 		while (t.tokens && t.tokens[i] != NULL)
// 		{
// 			// printf("[ %s ]\n", t.tokens[i]);
// 			if (parse(t.tokens) && t.tokens)
// 			{
// 			}
// 			i++;

// 		}
// 		execute(&t, &exit_code);
// 		// if (!t.tokens)
// 		// 	return (0);
// 	}
// 	return (exit_code);
// }
