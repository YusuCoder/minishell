
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

// Length of the 2D array
int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

// Check if the character is a number
int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*my_strjoin(const char *str1, const char *str2, const char *str3)
{
	char	*new_str;
	char	*ptr;
	int		str1_len;
	int		str2_len;
	int		str3_len;

	if (!str1 || !str2 || !str3)
		return (NULL);
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	str3_len = ft_strlen(str3);
	new_str = (char *)malloc(str1_len + str2_len + str3_len + 1);
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (*str1)
		*ptr++ = *str1++;
	while (*str2)
		*ptr++ = *str2++;
	while (*str3)
		*ptr++ = *str3++;
	*ptr = '\0';
	return (new_str);
}

// void	my_strcopy(char **dst, const char *src1, const char *src2, const char *src3)
// {
// 	char	*ptr;

// 	if (!src1 && !src2 && !src3)
// 	{
// 		*dst = NULL;
// 		return ;
// 	}
// 	ptr = *dst;
// 	printf("ptr = dst = %s\n", *dst);
// 	while (*src1)
// 		*ptr++ = *src1++;
// 	while (*src2)
// 		*ptr++ = *src2++;
// 	while (*src3)
// 		*ptr++ = *src3++;
// 	*ptr = '\0';
// }

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
