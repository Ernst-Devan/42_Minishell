/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:13:06 by dernst            #+#    #+#             */
/*   Updated: 2025/06/17 12:25:10 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parsing.h>

char	*define_expand(char *variable)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!variable)
		return (NULL);
	buffer = ft_calloc(ft_strlen(variable) + 3, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[j++] = EXPAND;
	while (variable[i])
	{
		buffer[j] = variable[i];
		j++;
		i++;
	}
	buffer[j++] = EXPAND;
	buffer[j] = '\0';
	return (buffer);
}

char	*replace_var(char *str, char **env)
{
	char	*variable;
	char	*buffer;

	variable = find_env(str, env);
	if (ft_strlen(variable) == 0)
		return (NULL);
	variable = define_expand(variable);
	if (!variable)
		return (NULL);
	buffer = ft_strdup(variable);
	if (!buffer)
		return (NULL);
	free(variable);
	return (buffer);
}

char	*detect_full_variable(char *input)
{
	char	*buffer;
	size_t	i;

	i = 0;
	buffer = calloc(ft_strlen(input) + 2, sizeof(char));
	if (!buffer)
		return (NULL);
	input++;
	if (*input == '?')
	{
		buffer[i++] = *input;
		buffer[i] = '\0';
		return (buffer);
	}
	while (*input)
	{
		if (!ft_isalnum(*input) && *input != '_')
			break ;
		buffer[i++] = (*input)++;
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

char	*adding_expand(t_expand *expand, char *variable, char **env, char quote)
{
	char	*expanded;

	expanded = replace_var(variable, env);
	if (quote == 0 && expanded)
	{
		expanded = skip_first_space(expanded);
		manage_space(&expanded);
	}
	expand->i += ft_strlen(variable);
	if (!expanded)
		return (expand->buffer);
	ft_strlcat(expand->buffer, expanded, expand->alloc);
	expand->j += ft_strlen(expanded);
	if (expanded && ft_strlen(expanded) > 0)
		free(expanded);
	return (expand->buffer);
}

char	*special_expand(t_shell shell, t_expand *expand)
{
	char	*error;

	error = ft_itoa(shell.error_code);
	ft_strlcat(expand->buffer, error, expand->alloc);
	expand->j += ft_strlen(error);
	expand->i += 2;
	free(error);
	return (expand->buffer);
}

size_t	need_expand(char *input, t_expand *expand, t_shell shell, char quote)
{
	char	*variable;

	variable = detect_full_variable(&input[expand->i]);
	if (!variable)
		return (1);
	else if (variable[0] == '?')
		expand->buffer = special_expand(shell, expand);
	else
		expand->buffer = adding_expand(expand, variable, shell.env, quote);
	free(variable);
	return (0);
}

size_t	manage_expand(t_shell shell, char **input)
{
	t_expand	expand;
	char		quote;

	if (!count_chars(*input, "$"))
	{
		return (SKIP);
	}
	if (init_expand(&expand, *input, shell))
		return (E_MALLOC);
	quote = 0;
	while ((*input)[expand.i])
	{
		inside_quote((*input)[expand.i], &quote);
		if (quote != '\'')
		{
			while ((*input)[expand.i] == '$')
			{
				if (need_expand(*input, &expand, shell, quote))
					break ;
			}
		}
		if ((*input)[expand.i])
			expand.buffer[expand.j++] = (*input)[expand.i++];
	}
	expand.buffer[expand.j] = '\0';
	free(*input);
	*input = expand.buffer;
	return (0);
}
