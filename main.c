/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:45 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/01 15:43:42 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*read_line(void)
{
	char	cwd[PATH_MAX];
	char	*line;
	char	prompt[PATH_MAX + 4];
	char	*last_component;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	// printf(CYAN"%s $\n"RESET, cwd);
	last_component = strrchr(cwd, '/');
	if (last_component == NULL)
		last_component = cwd;
	else
		last_component++;
	snprintf(prompt, sizeof(prompt), RED"~ %s: 🚀 "RESET, last_component);
	line = readline(prompt);
	if (line && *line != '\0')
		add_history(line);
	return (line);
}

void	set_data(t_data *data, char **envp, int *exit_code)
{
	data->exit_code = exit_code;
	data->cmd_list = NULL;
	data->cmd_num = 0;
	data->tokens = NULL;
	_init_terminal();
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

void	check_and_execute(t_data *data)
{
	expand(data->tokens, data->env, data);
	cmd_list_handler(data);
	quote_handing(data->cmd_list);
	redir_list_handler(data);
	heredoc_handler(data);
	execute(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	int		exit_code;

	(void)argv;
	(void)argc;
	exit_code = 0;
	set_data(&data, envp, &exit_code);
	while (1)
	{
		_handle_signals(INIT);
		line = read_line();
		if (!line)
			break ;
		data.tokens = tokenizing(line);
		free(line);
		if (!parse(data.tokens, &data) && data.tokens)
			check_and_execute(&data);
		else
		{
			free_array(data.tokens);
			continue ;
		}
	}
	free_exit(&data, exit_code);
}
