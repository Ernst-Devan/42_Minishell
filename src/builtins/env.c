/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:20:20 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 15:49:28 by njooris          ###   ########.fr       */
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
	while (env && env[i])
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
