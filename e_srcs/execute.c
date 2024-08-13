/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/12 20:01:49 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_wrong_command(char *arg, int *exit_code)
{
	write(2, "minishell: ", 12);
	write(2, arg, ft_strlen(arg));
	write(2, ": command not found\n", 21);
	*exit_code = 127;
}

void	execute_builtin(char **args, char ***env, int *exit_code)
{
	if (is_cd(args[0]))
		execute_cd(args, *env, exit_code);
	else if (is_pwd(args[0]))
		execute_pwd(exit_code);
	else if (is_env(args[0]))
		execute_env(*env, exit_code);
	else if (is_echo(args[0]))
		execute_echo(args, exit_code);
	else if (ft_strcmp(args[0], "export") == 0)
		execute_export(args, env, exit_code);
	else if (ft_strcmp(args[0], "unset") == 0)
		execute_unset(args, env, exit_code);
	else if (ft_strcmp(args[0], "exit") == 0)
		execute_exit(args, exit_code);
	else
		return ;
}

void	execute(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	while (current != NULL)
	{
		if (current->args[0] == NULL)
			data->exit_code = 0;
		else if (is_builtin(current->args[0]))
			execute_builtin(current->args, &data->env, data->exit_code);
		else
			print_wrong_command(current->args[0], data->exit_code);
		current = current->next;
	}
	list_free(&data->cmd_list);
}

// void	execute(t_command *cmd, int *exit_code)
// {
// 	if (cmd->tokens[0] == NULL)
// 		*exit_code = 0;
// 	else if (is_builtin(cmd->tokens[0]))
// 		execute_builtin(cmd->tokens, &cmd->envp, exit_code);
// 	else
// 		print_wrong_command(cmd->tokens[0], exit_code);
// }

// void	execute(t_command *cmd, int *exit_code)
// {
// 	int i = 0;
// 	while (cmd->sub_command->sub_cmd_array[i])
// 	{
// 		printf("%s\n", cmd->sub_command->sub_cmd_array[i]);
// 		i++;
// 	}
// 	if (cmd->tokens[0] == NULL)
// 		*exit_code = 0;
// 	else if (is_builtin(cmd->tokens[0]))
// 		execute_builtin(cmd->tokens, &cmd->envp, exit_code);
// 	else
// 		print_wrong_command(cmd->tokens[0], exit_code);
// }
