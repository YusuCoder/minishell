/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:58:55 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/12 11:55:46 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	counts number of subcommands and the arguments of subcommands, after getting the count
	sets them to their variables in structs
*/
// int	token_count(t_command *cmd, char **tokens, int i, int j)
// {
// 	int	counter;

// 	counter = 0;
// 	while (tokens[i] &&  ft_strncmp(tokens[i], "|", 1) != 0)
// 	{
// 		counter++;
// 		i++;
// 	}
// 	cmd->sub_command[j].sub_argc_count = counter;
// 	return (counter);
// }


/*
	this function counts number of commands in general that tokens has
*/
// int	count_cmds(char	**token)
// {
// 	int	i;
// 	int	counter;

// 	i = 0;
// 	counter = 1;
// 	while (token[i])
// 	{
// 		if(ft_strncmp(token[i], "|", 1) == 0)
// 		{
// 				counter++;
// 		}
// 		i++;
// 	}
// 	return (counter);
// }
/*
	this function allocates the memory for each sub commands and counts the number of commands and sets the count
	to cmd->argc so you always have the exect command count in that variable, after it will count each subcommand
	and the number of arguments each subcommand has, after set each subcommand to cmd->sub_command and their arguments
	to cmd->sub_command.sub_argc_count or in other words to sub_argc_count from subcommands struct
*/
// int	count_commands(char **tokens, t_command *cmd)
// {
// 	int	i = 0;
// 	int	j = 0;

// 	if (!tokens || !cmd)
// 		return -1;
// 	cmd->cmd_num = count_cmds(tokens);
// 	cmd->sub_command = (t_sub_commands *)malloc((cmd->cmd_num) * sizeof(t_sub_commands));
// 	if (!cmd->sub_command)
// 		return (-1);
// 	i = 0;
// 	j = 0;
// 	while (tokens[i])
// 	{
// 		i = i + token_count(cmd, tokens, i, j);
// 		if (tokens[i] && ft_strncmp(tokens[i], "|", 1) == 0)
// 			i++;
// 		j++;
// 	}
// 	return (0);
// }

// int main() {
// 		char *tokens[] = {
// 		"echo", "-n", "hello", "|",
// 		"grep", "world", "|",
// 		"wc", "-l",
// 		NULL
// 	};

// 	t_command cmd;

// 	int result = count_commands(tokens, &cmd);

// 	if (result == -1) {
// 		printf("Error allocating memory.\n");
// 		return 1;
// 	}

// 	printf("Total commands: %d\n", cmd.cmd_num);
// 	int i = 0;
// 	while (i < cmd.cmd_num)
// 	{
// 		printf("Command %d has %d arguments.\n", i + 1, cmd.sub_command[i].sub_argc_count);
// 		i++;
// 	}
// 	free(cmd.sub_command);

// 	return 0;
// }

