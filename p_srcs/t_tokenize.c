/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/14 12:08:38 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*In this function im checking for the quotes "" or '' if the current idex is " or ' then
  the function iterates through the string untill it finds the closing quote to return its index
*/
int	matching_quotes(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == DQUOTE)
	{
		i++;
		while (str[i] != DQUOTE && str[i])
			i++;
	}
	else if (str[i] == SQUOTE)
	{
		i++;
		while (str[i] != SQUOTE && str[i])
			i++;
	}
	return (i);
}

char	**tokenizing(const char *str)
{
	char	**t;
	int		words;
	int		words1;
	int		x;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	words = count_words(str, i);
	if (words < 1)
		return (NULL);
	t = (char **)malloc(sizeof(t) * (words + 1));
	if (!t)
		return (NULL);
	words1 = 0;
	x = 0;
	if (take_tokens(t, str, words1, x) < 0)
		return (NULL);
	t[words] = NULL;
	return (t);
}
// int	main(void)
// {
// 	const char *str = "'Hello<'|'>>>World'";
// 	char **tokens = tokenizing(str);
// 	if (tokens)
// 	{
// 		int i = 0;
// 		while (tokens[i])
// 		{
// 			printf("[ %s ]   ", tokens[i]);
// 			i++;
// 		}
// 		free(tokens);
// 	}
// 	return (0);
// }
