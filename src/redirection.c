// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>

int	open_redirection(t_table *table, char in[NAME_MAX], char out[NAME_MAX])
{
	if (in[0])
		table->in = open(in, O_RDONLY);
	else
		table->in = 0;
	if (out[0])
		table->out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		table->out = 1;
	if (table->out < 0)
			return(1);
	return (0);
}

char	*insert_redirection(t_table *table, char *input)
{
	char	*buffer;
	char	in[NAME_MAX];
	char	out[NAME_MAX];
	int		count;
	int		i;

	ft_strlcpy(in, "\0", 1);
	ft_strlcpy(out, "\0", 1);
	buffer = malloc((ft_strlen(input) + 1) * sizeof(char));
	i = 0;
	while (*input)
	{
		if (*input == '<' || *input == '>')
		{
			count = ft_strlen_c(input, ": ");
			if (*input == '<')
			{
				ft_strlcpy(in, input + 1, count);
			}
			else if (*input == '>')
			{
				ft_strlcpy(out, input + 1, count);
			}
			input += count;
		}
		buffer[i] = *input;
		i++;
		input++;
	}
	open_redirection(table, in, out);
	buffer[i] = '\0';
	return (buffer);
}
