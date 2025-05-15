#include <libft.h>
#include <parsing.h>
#include <stddef.h>
#include <stdio.h>

char *replace_var(char *str, char **env) {
	char *variable;
	char *buffer;

	variable = find_env(str, env);
	if (!variable)
		return ("\0");
	buffer = ft_strdup(variable);
	if (!buffer)
		return ("\0");
	return (buffer);
}

void	check_var_env(char **list_env,char *buffer, size_t *i, size_t *j, size_t buffer_size)
{
	buffer[*i] = '\0';
	ft_strlcat(buffer, list_env[*j], buffer_size);
	*i += ft_strlen(list_env[*j]);
	*j += 1;
}
// 
// CHECK WITH THE QUOTES CAUSE I THINK IT DONT WORK



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

char	find_env_end(char *str, char *characters, char quote)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == quote)
			return (*str);
		while (characters[i])
		{
			if (*str == characters[i])
				return (*str);
			i++;
		}
		i = 0;
		str++;
	}
	return (*str);
}

// Change the : by the new separator inside all the command (unwritable char)

char *detect_full_variable(char *input)
{
	char	*temp;

	size_t	i;

	i = 0;
	temp = malloc(ft_strlen(input) + 1);
	if (!temp)
		return (NULL);
	while (*input)
	{
		if (!ft_isalpha(*input))
			break;
		temp[i] = *input;
		i++;
		input++;
	}
	temp[i] = '\0';
	return (temp);
}


//size_t	detect_others_expand(char *input, size_t *i)
//{
//	if (ft_strlen(&input[*i]) <= 1)
//		return (1);
	//if (ft_strlen(&input[*i]) <= 1)
	//	return (2);
	//if (input[*i + 1] && check_delimiter(input[*i + 1], "\"\'$-!0_#@*"))
	//{
	//	*i += 2;
	//	if (check_delimiter(input[*i - 1], "\'\""))
	//		return (1);
	//}
	//return (0);
//}

char *expand_env(char *input, char **env)
{
	char	*temp;
	char	*variable;
	char	quote;
	size_t	i;
	size_t	j;

	temp = ft_calloc(500, sizeof(char)); // Make a function count the allocation needed
	quote = 0;
	i = 0;
	j = 0;
	while (input[i])
	{
		inside_quote(input[i], &quote);
		if (quote != '\'')
		{	
			while (input[i] == '$')
			{
				//if (detect_others_expand(input, &i) == 1 || detect_others_expand(input, &i) == 2)
				//	break;
				if (input[i] != '$')
					break;
				variable = replace_var(detect_full_variable(&input[++i]), env);
				i += ft_strlen_c(&input[i], find_env_end(&input[i], ":$-|<>", quote));
				ft_strlcat(temp, variable, 500);
				j += ft_strlen(variable);
			}
			if (!input[i])
				break;
		}
		temp[j] = input[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	free(input);
	return (temp);
}
