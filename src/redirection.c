// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>

// Check the open

int	open_in(t_cmd *cmd, char in[NAME_MAX])
{
	if (in[0] != '\0')
		cmd->in = open(in, O_RDONLY);
	else
		cmd->in = 0;
	return (0);
}

int	open_out(t_cmd *cmd, char out[NAME_MAX])
{
	if (out[0] != '\0')
		cmd->out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->out = 1;
	if (cmd->out < 0)
		return(1);
	return (0);
}

char	*insert_redirection(t_table *table, char *input)
{
	char	*temp_input;
	char	*buffer;
	char	in[NAME_MAX];
	char	out[NAME_MAX];
	int		count;
	int		i;

	(void)table;
	temp_input = input;
	ft_strlcpy(in, "\0", 1);
	ft_strlcpy(out, "\0", 1);
	buffer = malloc((ft_strlen(temp_input) + 1) * sizeof(char));
	if (!buffer)
		return(NULL);
	i = 0;
	while (*temp_input)
	{
		if (*temp_input == '<' || *temp_input == '>')
		{
			count = ft_strlen_c(temp_input, ": ");
			if (*input == '<')
				ft_strlcpy(in, temp_input + 1, count);
			else if (*temp_input == '>')
				ft_strlcpy(out, temp_input + 1, count);
			temp_input += count;
		}
		buffer[i] = *temp_input;
		i++;
		temp_input++;
	}
	//open_redirection(table, in, out);
	buffer[i] = '\0';
	free(input);
	return (buffer);
}
