#include <libft.h>
#include <parsing.h>
#include <stddef.h>
#include <stdio.h>
#include <stddef.h>
#include <stdio.h>

// QUESTION ABOUT THIS CASE $$PWD
// echo "$PWD" Not WORK
// echo $"PWD" Must print PWD
// echo $PWD-n 
// echo $PWD -n WORK
// ls FILE -la work test it
// $$ ERROR
// $? MANAGE IT
// Test expand with all other delimiter
//!!!!! FOR TODAY
// echo $$PWD -> return nothing 
// echo $$$PWD -> return PWD
// echo $'PWD' return PWD
// echo $ -> return $
// echo $PWD$ -> return the pwd + $
// echo $$$$$$$$$$$ -> ERROR
// echo$PWD -> LEAK INSIDE CHECK_COMMAND -> FT_SPLIT
// echo $_ -> alphanumeric
// echo $0 -> minishell
// echo $012 MUST DISPLAY SOMETHING !!
// the first bytes must be not a digit
// echo$PWD$PWD -> LEAKS !!!! 
// Change the : by the new separator inside all the command (unwritable char)

char	*replace_var(char *str, char **env)
{
	char	*variable;
	char	*buffer;

	variable = find_env(str, env);
	if (!variable)
		return ("\0");
	buffer = ft_strdup(variable);
	if (!buffer)
		return ("\0");
	return (buffer);
}

char	*detect_full_variable(char *input)
{
	char	*buffer;
	size_t	i;

	i = 0;
	buffer = malloc(ft_strlen(input) + 2);
	if (!buffer)
		return (NULL);
	while (*input)
	{
		input++;
		if (!ft_isalnum(*input) && *input != '?' && *input != '_')
			break ;
		buffer[i++] = *input;
	}
	buffer[i] = '=';
	buffer[i + 1] = '\0';
	if (ft_strlen(buffer) == 1 || ft_isdigit(buffer[0]))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*adding_expand(t_expand *expand, char *variable, char **env)
{
	char	*expanded;

	expanded = replace_var(variable, env);
	expand->i += ft_strlen(variable);
	ft_strlcat(expand->buffer, expanded, 500);
	expand->j += ft_strlen(expanded);
	if (expanded && ft_strlen(expanded) > 0)
		free(expanded);
	return (expand->buffer);
}

char	*special_expand(t_shell shell, t_expand *expand)
{
	char	*error;

	error = ft_itoa(shell.error_code);
	ft_strlcat(expand->buffer, error, 500);
	free(error);
	expand->j += ft_strlen(error);
	expand->i += 2;
	return (expand->buffer);
}

char	*need_expand(char *input, t_expand *expand, t_shell shell)
{
	char *variable;

	variable = detect_full_variable(&input[expand->i]);
	if (!variable)
		return (NULL);	
	else if (variable[0] == '?')
		expand->buffer = special_expand(shell, expand);
	else
		expand->buffer = adding_expand(expand, variable, shell.env);
	free(variable);
	return (expand->buffer);

}

char *manage_expand(char *input, t_shell shell)
{
	t_expand	expand;
	char		*test;
	char		quote;

	if (init_expand(&expand))
		return(NULL);
	quote = 0;
	while (input[expand.i])
	{	
		inside_quote(input[expand.i], &quote);
		if (quote != '\'')
		{
			while (input[expand.i] == '$')
			{
				test = need_expand(input, &expand, shell);
				if (!test)
					break;
			}
		}
		if (input[expand.i])
			expand.buffer[expand.j++] = input[expand.i++];
	}
	expand.buffer[expand.j] = '\0';
	free(input);
	return (expand.buffer);
}
