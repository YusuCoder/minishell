
#include "../includes/minishell.h"

void	clean_tokens(t_data *data)
{
	free_array(data->tokens);
	data->tokens = NULL;
	free_list(&data->cmd_list);
	data->cmd_list = NULL;
}
