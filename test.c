#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

void	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, orig_termios);
	raw = *orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(const struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

char	*readline(const char *prompt)
{
	struct termios	orig_termios;
	char			buffer[MAX_LINE_LENGTH];
	int				buffer_pos;
	int				c;

	enable_raw_mode(&orig_termios);
	buffer_pos = 0;
	printf("%s", prompt);
	fflush(stdout);
	while (1)
	{
		c = getchar();
		if (c == '\n')
		{
			buffer[buffer_pos] = '\0';
			printf("\n");
			break ;
		}
		if (c == 127 || c == 8)
		{
			if (buffer_pos > 0)
			{
				buffer_pos--;
				printf("\b \b");
				fflush(stdout);
			}
			continue ;
		}
		if (isprint(c) && buffer_pos < MAX_LINE_LENGTH - 1)
		{
			buffer[buffer_pos++] = (char)c;
			putchar(c);
			fflush(stdout);
		}
	}
	buffer[buffer_pos] = '\0';
	disable_raw_mode(&orig_termios);
	return (strdup(buffer));
}

int	main(void)
{
	char	*input;

	while ((input = readline("prompt> ")) != NULL)
	{
		if (strlen(input) > 0)
		{
			printf("You entered: %s\n", input);
		}
		free(input);
	}
	return (0);
}
