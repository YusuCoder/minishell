/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:13:50 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/20 00:20:01 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_token_heredoc(char *token, char *e_name)
{
	char	*x;
	char	*res;
	char	*final_res;
	char	*c;

	x = get_x_string_heredoc(token);
	c = get_c_string(token);
	res = ft_strjoin(x, e_name);
	free(x);
	if (e_name != NULL)
		free(e_name);
	final_res = ft_strjoin(res, c);
	free(res);
	free(c);
	return (final_res);
}
