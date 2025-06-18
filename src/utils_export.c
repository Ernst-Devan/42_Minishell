/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:56:16 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 13:10:02 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"
#include "env_manage.h"
#include "builtins.h"

char	*find_first(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env[j], ft_strlen(env[j] + 1)) >= 0)
			j = i;
		i++;
	}
	return (env[j]);
}

char	*find_n(char **env, int nb)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (count_bigger_than(env[i], env) == nb)
			return (env[i]);
		i++;
	}
	return (env[i]);
}

int	count_bigger_than(char *str, char **env)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str) + 1) > 0)
			count++;
		i++;
	}
	return (count);
}

int	var_env_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

int	find_env_variable(char **env, char *str)
{
	int	i;
	int	len;

	len = var_env_len(str);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0
			&& (env[i][len] == '=' || !env[i][len]))
			return (i);
		i++;
	}
	return (-1);
}
