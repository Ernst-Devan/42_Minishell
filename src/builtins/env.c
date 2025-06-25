/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:20:20 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 18:17:04 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing.h"

char	*find_env(char *str, char **env)
{
	int	count;
	int	i;

	i = 0;
	count = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], count) == 0)
		{
			if (ft_strlen(env[i]) == 0)
				return (NULL);
			return (env[i] + count);
		}
		i++;
	}
	return (NULL);
}

int	can_print_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!can_print_env(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
}

int	env_builtin(char **env, t_cmd cmd)
{
	if (cmd.args[1])
		return (1);
	print_env(env);
	return (0);
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
	adding_inside_var(input, &buffer, &i);
	buffer[i] = '=';
	buffer[i + 1] = '\0';
	if (ft_strlen(buffer) == 1 || ft_isdigit(buffer[0]))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
