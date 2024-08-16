/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/16 16:36:13 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"
// // /*Gets the string from env SHLVL=1 and iterates untill it reaches '=' then it extracts a substring 'SHELL='
// //   after it will convert '1' to integer using atoi then increments it by one then converts it back to string.*/
// char	*shlvl_handler(char *str)
// {
// 	char	*number;
// 	char	*name;
// 	int		i;

// 	i = 0;
// 	while (str[i] != '=')
// 		i++;
// 	name = ft_substr(str, 0, i + 1);
// 	number = ft_itoa(ft_atoi(str + i + 1) + 1);
// 	str = ft_strjoin(name, number);
// 	free(name);
// 	free(number);
// 	return (str);
// }
// /*---Creating the list of enviroment variables to the t_cmd struct---*/
// void	_init_env_shlvl(t_command *cmd, char **envp)
// {
// 	int			i;
// 	char		*res;
// 	t_ryusupov	*lst;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp("SHLVL", envp[i], 5) == 0)
// 		{
// 			res = shlvl_handler(envp[i]);
// 			if (ft_strlcpy(envp[i], res, ft_strlen(res) + 1))
// 			{
// 				lst = ft_lstnew(ft_strdup(envp[i]));
// 				_free_it(&res);
// 			}
// 		}
// 		else
// 			lst = ft_lstnew(ft_strdup(envp[i]));
// 		ft_lstadd_back(cmd->env, lst);
// 		i++;
// 	}
// }
// /*Terminal ctrl setting disables echo messages of ctrl signals using flag ECHOCTRL*/
// void	_init_terminal(t_command *cmd, char **envp)
// {
// 	struct termios	term;

// 	if (tcgetattr(0, &term) != 0)
// 		_err_msg("Error!\n", EXIT_FAILURE);
// 	term.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(0, TCSANOW, &term) != 0)
// 		_err_msg("Error!\n", EXIT_FAILURE);
// 	cmd->env = (t_ryusupov **)malloc(sizeof(t_ryusupov));
// 	if (!cmd->env)
// 		_err_msg("Allocation error!\n", EXIT_FAILURE);
// 	*(cmd->env) = NULL;
// 	cmd->tokens = NULL;
// 	_init_env_shlvl(cmd, envp);
// 	cmd->exit_code = 0;
// 	_handle_signals(INIT);
// }
