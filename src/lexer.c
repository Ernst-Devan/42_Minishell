// DONT FORGOT TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"



// $PWD= work also he must dont work
// Many VARIABLE ALSO BUG IN THE MIDDLE


char *replace_var(char *str, char **env)
{
    char    *buffer;
    char    *variable;
    int     count;

    buffer = malloc((1024 * 4) * sizeof(char));
    count = ft_strlen_c(str, " ");
    ft_strlcpy(buffer, str + 1, count);
    variable = find_env(buffer, env);
	if (!variable)
		return ("\0");
    free(buffer);
    return (variable);
}

char *replace_env_variable(char *input, char **env)
{
    char    *buffer;
    char    *variable;
    int     count;
    int     i;
    int     j;

    buffer = malloc((1024 * 4) * sizeof(char));
    i = 0;
    j = 0;
    count = 0;
    while (input[i])
    {
        if (input[i] == '$')
        {
            count = ft_strlen_c(&input[i], " ");
            variable = replace_var(&input[i], env);
            buffer = ft_strjoin(buffer, variable);
            j += ft_strlen(variable);
            i += count;
        }
        buffer[j] = input[i];
        j++;
        i++;
    }
    buffer[j] = '\0';
    free(input);
    return (buffer);
} 

// Not needed to use ':' We can just use space 


char	*skip_characters(char *input, char c)
{
	while (*input == c && *input)
		input++;
	return (input);
}

char	*check_redirection(char *input, char *buffer, int *i)
{
	if (*input == '<' || *input == '>')
	{
		buffer[*i] = *input;
		(*i)++;
		input++;
		input = skip_characters(input, ' ');
		while (*input && check_delimiter(*input)!= 1)
		{
			buffer[*i] = *input;
			(*i)++;
			input++;
		}
		input = skip_characters(input, ' ');
		buffer[*i] = ':';
		(*i)++;
	}
	return (input);
}

char	*lexer(char *input, char **env)
{
	char	*buffer;
	char	*input_adress;
	int		i;

	(void)env;
	input_adress = input;
	i = 0;

	buffer = malloc(((ft_strlen(input) + 1) * 5) * sizeof(char));
	//Protect Malloc!!

	input = skip_characters(input, ' ');
	while(*input)
	{
		if (check_delimiter(*input) == 1)
		{	
			buffer[i++] = ':';
			input = skip_characters(input, ' ');
			input = check_redirection(input, buffer, &i);
			if (check_delimiter(*input) == 1)
			{
				input = check_redirection(input, buffer, &i);
				buffer[i++] = *input++;
				buffer[i++] = ':';
				input = skip_characters(input, ' ');
			}
		}
		else
			buffer[i++] = *input++;
	}
	buffer[i] = '\0';
	free(input_adress);
	return (buffer);
}

