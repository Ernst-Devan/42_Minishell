#include "parsing.h"
#include "libft.h"

size_t	count_fist_space(char *input)
{
	size_t	count;
	
	count = 0;
	while (*input && ft_isspace(*input))
	{
		count++;
		input++;
	}
	return (count);
}

void	skip_space(char **buffer, char *input, size_t *i, size_t *j)
{
	if (ft_isspace(input[*i]))
	{
		(*buffer)[*j] = SEPARATOR;
		*j += 1;
		while (input[*i] && ft_isspace(input[*i]))
			*i += 1;
	}
}

char	*manage_space(char *input)
{
	char	*buffer;
	char	quote;
	size_t	i;
	size_t	j;

	buffer = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	quote = 0;
	i = count_fist_space(input);
	j = 0;
	while (input[i])
	{
		if (quote == 0)
			skip_space(&buffer, input, &i, &j);
		if (!input[i])
			break;
		inside_quote(input[i], &quote);
		buffer[j] = input[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	free(input);
	return (buffer);
}
