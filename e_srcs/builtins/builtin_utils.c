
#include "../../includes/minishell.h"

// Custom strndup function
char	*my_strndup(const char *str, int len)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(len + 1);
	if (new_str == NULL)
		return NULL;
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

// Custom realloc function
void	*my_realloc(void *ptr, int old_size, int new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

// // Custom strcpy function
// char *my_strcpy(char *dest, const char *src)
// {
// 	char *ptr;

// 	ptr = dest;
// 	while (*src)
// 	{
// 		*ptr++ = *src++;
// 	}
// 	*ptr = '\0';
// 	return dest;
// }
