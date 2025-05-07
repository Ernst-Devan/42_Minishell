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

  while (i < count_env) 
	{
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
	char	*buffer;
	char	*input_adress;
	size_t	i;
	size_t	buffer_size;
	char	quote;
	(void)env;


	quote = 0;
	buffer_size = ft_strlen(input) + count_characters(input, DELIMITER) * 10 + 1;
	i = 0;
	buffer = malloc(buffer_size * sizeof(char));
	if (!buffer)
		return (NULL);
	input_adress = input;
	while (*input)
	{
		if (inside_quote(*input, &quote))
			buffer[i++] = *input++;
		else
		{
			if (check_delimiter(*input, "<>| ") == 1)
			{
				if (*input == ' ')
					input++;
				buffer[i++] = ':';
				while(check_delimiter(*input, "<>|") == 1)
					buffer[i++] = *input++;
				if (buffer[i - 1] != ':')
					buffer[i++] = ':';
				if (*input == ' ')
					input++;
			}
			if (*input && *input != '\'' && *input != '\"')
				buffer[i++] = *input++;
		}
	}
	buffer[i] = '\0';
	free(input_adress);
	return (buffer);
}
