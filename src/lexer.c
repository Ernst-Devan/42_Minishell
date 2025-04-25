/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:13:07 by dernst            #+#    #+#             */
/*   Updated: 2025/04/22 11:13:55 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <stddef.h>

// $$ SEGFAULT

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

char **insert_list_env(char *input, char **env) {
  char **list_env;
  char temp[ENV_MAX];
  char *variable;
  size_t count_env;
  size_t i;
  size_t increase;

  count_env = count_characters(input, "$");
  list_env = malloc((count_env + 1) * sizeof(char *));
  if (!list_env)
    return (NULL);
  i = 0;

  while (i < count_env) {
    input = ft_strchr(input, '$');
    input++;
    increase = ft_strccpy(temp, input, ' ');
    input += increase;
	ft_strlcat(temp, "=" , ENV_MAX);
    variable = replace_var(temp, env);
	list_env[i] = ft_strdup(variable);
    ft_strlcpy(temp, "\0", 1);
    i++;
  }
  list_env[i] = NULL;
  return (list_env);
}

// Not needed to use ':' We can just use space

char *skip_characters(char *input, char c) {
  while (*input == c && *input)
    input++;
  return (input);
}

char *check_redirection(char *input, char *buffer, size_t *i) {
  input = skip_characters(input, ' ');
  if (*input == '<' || *input == '>') {
    buffer[*i] = *input;
    (*i)++;
    input++;
    input = skip_characters(input, ' ');
    while (*input && check_delimiter(*input, DELIMITER) != 1) {
      buffer[*i] = *input;
      (*i)++;
      input++;
    }
    buffer[*i] = ':';
    (*i)++;
  }
  return (input);
}

void	check_var_env(char **list_env,char *buffer, size_t *i, size_t *j, size_t buffer_size)
{
	buffer[*i] = '\0';
	ft_strlcat(buffer, list_env[*j], buffer_size);
	*i += ft_strlen(list_env[*j]);
	*j += 1;
}

char *lexer(char *input, char **env) 
{
	char	**list_env;
	char	*buffer;
	char	*input_adress;
	size_t	i;
	size_t	j;
	size_t	buffer_size;

	list_env = insert_list_env(input, env);
	buffer_size = lstrlen(list_env) + ft_strlen(input) + count_characters(input, DELIMITER) * 2 + 1;
	i = 0;
	j = 0;
	buffer = malloc(buffer_size * sizeof(char));
	if (!buffer)
		return (NULL);
	input_adress = input;
	input = skip_characters(input, ' ');
	while (*input) 
	{
		if (*input == '$')
		{
			input += ft_strlen_c(input, " ");
			check_var_env(list_env, buffer, &i,&j, buffer_size);
		}
		if (*input == '\0')
			break;
		if (check_delimiter(*input, "<>| ") == 1)
		{
			buffer[i++] = ':';
			input = skip_characters(input, ' ');
			while(check_delimiter(*input, "<>|") == 1)
				buffer[i++] = *input++;
			if (buffer[i - 1] != ':')
				buffer[i++] = ':';
			input = skip_characters(input, ' ');
		}
		else
			buffer[i++] = *input++;
	}
	buffer[i] = '\0';
	free(input_adress);
	return (buffer);
}
