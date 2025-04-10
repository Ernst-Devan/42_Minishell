// DONT FORGOT TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"


int ft_strlen_c(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

char *replace_var(char *str, char **env)
{
    char    *buffer;
    char    *variable;
    int     count;

    buffer = malloc((1024 * 4) * sizeof(char));
    count = ft_strlen_c(str, ' ');
    ft_strlcpy(buffer, str + 1, count);
    variable = find_env(buffer, env);
	if (!variable)
		return ("\0");
    free(buffer);
    return (variable);
}

// $PWD= work also he must dont work
// Many VARIABLE ALSO BUG IN THE MIDDLE

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
            count = ft_strlen_c(&input[i], ' ');
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

size_t check_delimiter(char c)
{
    char delimiter[7] = {" <>|-&\0"};
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (c == delimiter[i])
            return (1);
        i++;
    }
    return (0);
}


// Not needed to use ':' We can just use space 

char    *lexer(char *input, char **env)
{
    char *buffer;  
    int i;
    int a;

    i = 0;
    a = 0;
    input = replace_env_variable(input, env);
    buffer = malloc((ft_strlen(input) * 2) * sizeof(char));
    while (input[a])
    {
        if (check_delimiter(input[a]) == 1)
        {
            if (buffer[i - 1] == ':' && input[a] == ' ')
                a++;
            else
            {
                if (buffer[i - 1] != ':')
                {
                    buffer[i] = ':';
                    i++;
                }
                if (input[a] != ' ')
                {
                    buffer[i] = input[a];
                    i++;
                    a++;
                }
            }
        }
        else 
        {
            buffer[i] = input[a];
            i++;
            a++;
        }
    }
    buffer[i] = '\0';
    free(input);
    return (buffer);
}

