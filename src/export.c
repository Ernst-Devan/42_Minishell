/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:52:31 by njooris           #+#    #+#             */
/*   Updated: 2025/04/14 10:59:05 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

int	var_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

int	find_env_variable(char **env, char *str)
{
	int	i;
	int	len;

	len = var_env_len(str) + 1;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], env, len))
			return (i);
		i++;
	}
	return (-1);
}

int	add_variable_env(char **env, char *data)
{
	char	**temp;
	int		i;
	int	size_env;
	int	nb_row;

	nb_row = size_of_env(env) + 1;
	temp = malloc(nb_row + 1);
	if (!temp)
		return (1);
	set_env_null(temp, nb_row);
	i = 0;
	while (i < nb_row)
	{
		temp[i] = ft_strdup(env[i]);
		if (!temp[i])
		{
			free_lstr(temp);
			return (1);
		}
		i++; 
	}
	free_lstr(env);
	temp[i] = data;
	env = temp;
	return (0);
}

int	edit_variable_env(char **env, char *data)
{
	int	i;
	int	j;

	i = find_env_variable(env, data);
	free(env[i]);
	env[i] = data;
	return (0);
}

int	export(t_table table, char **env)
{
	int	len;
	int	check;

	len = var_env_len(table.cmds->args);
	check = find_env_variable(env, table.cmds->args);
	if (check == -1)
		add_variable_env(env, table.cmds->args);
	else if (table.cmds->args[len] == '=')
		edit_variable_env(env, table.cmds->args);
	return (0);
}