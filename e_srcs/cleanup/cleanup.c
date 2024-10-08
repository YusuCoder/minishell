/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:00 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/20 11:52:18 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(t_data *data)
{
	free_array(data->tokens);
	data->tokens = NULL;
	free_cmd_list(&data->cmd_list);
	data->cmd_list = NULL;
}
