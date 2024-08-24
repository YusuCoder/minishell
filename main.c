
#include "./includes/minishell.h"

char	*read_line(char *line)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	printf(CYAN"%s $\n"RESET, cwd);
	line = readline(">>> ");
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
	_init_terminal();
	set_data(&data, envp, &exit_code);
	while (1)
	{
		_handle_signals(RES, &data);
		line = read_line(line);
		if (!line)
			break ;
		// expand_heredoc(&line, data.env, &data);
		// printf("%s\n", line);
		data.tokens = tokenizing(line);
		free(line);
		int i = 0;
		while (data.tokens && data.tokens[i] != NULL)
		{
			if (!parse(data.tokens, &data) && data.tokens)
			{
				expand_heredoc(data.tokens, data.env, &data);
 				cmd_list_handler(&data);
				redir_list_handler(&data);
				quote_handing(data.cmd_list);
				heredoc_handler(&data);
				// expand_heredoc(&data.cmd_list->heredoc_input, data.env, &data);
				execute(&data);
			}
			else
				break ;
			i++;
		}
	}
	free_exit(&data, exit_code);
}

