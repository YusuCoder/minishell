
#include "../includes/minishell.h"

int	is_builtin_cmd_only(t_data *data)
{
	if (data->cmd_num == 1
		&& is_builtin(data->cmd_list->args[0])
		&& data->cmd_list->is_heredoc == 0
		&& data->cmd_list->is_redir_input == 0
		&& data->cmd_list->is_redir_output == 0)
	{
		execute_builtin(data, data->cmd_list->args);
		return (1);
	}
	else
		return (0);
}

int	is_executable(char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, R_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (1);
		}
	}
	return (0);
}

// int	is_path(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '/')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

char	*set_cmd_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (str);
		i++;
	}
	return (NULL);
}

void	print_wrong_command(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": command not found");
	*exit_code = 127;
}

void	print_wrong_path(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": No such file or directory");
	*exit_code = 127;
}
