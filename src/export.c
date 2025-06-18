/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:52:31 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 12:57:43 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"
#include "env_manage.h"
#include "builtins.h"

int	add_variable_env(char ***env, char *data)
{
	char	**temp;
	int		i;
	int		nb_row;

	nb_row = size_of_env(*env);
	temp = malloc(sizeof(char *) * (nb_row + 2));
	if (!temp)
		return (1);
	temp[nb_row + 1] = NULL;
	i = 0;
	while (i < nb_row)
	{
		temp[i] = ft_strdup((*env)[i]);
		if (!temp[i])
			return (free_lstr(temp), 1);
		i++;
	}
	free_lstr(*env);
	temp[i] = ft_strdup(data);
	if (!temp[i])
		return (1);
	*env = temp;
	return (0);
}

int	edit_variable_env(char ***env, char *data)
{
	int	i;

	i = find_env_variable(*env, data);
	free((*env)[i]);
	(*env)[i] = ft_strdup(data);
	if (!(*env)[i])
	{
		(*env)[i] = NULL;
		return (1);
	}
	return (0);
}

void	print_export_one_val(char *str)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=')
		{
			write(1, "\"", 1);
			check = 1;
		}
		if (!str[i + 1] && check == 1)
			write(1, "\"", 1);
		i++;
	}
}

void	export_without_param(char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(find_n(env, i), "_=", 2) != 0)
		{
			str = find_n(env, i);
			write(1, "declare -x ", ft_strlen("declare -x "));
			print_export_one_val(str);
			write(1, "\n", 1);
		}
		i++;
	}
}

int	export(t_cmd cmd, char ***env)
{
	int	i;
	int	check;
	int	check2;

	check2 = 0;
	if (!cmd.args[1])
		return (export_without_param(*env), 0);
	i = 0;
	while (cmd.args[++i])
	{
		if (cmd.args[i] && !ft_isalpha(cmd.args[i][0]))
		{
			if (check2++ == 1)
				printf("Bad param(s)\n");
		}
		else
		{
			check = find_env_variable(*env, cmd.args[i]);
			if (check == -1 && add_variable_env(env, cmd.args[i]))
				return (1);
			else if (cmd.args[i][var_env_len(cmd.args[i])] == '=')
				edit_variable_env(env, cmd.args[i]);
		}
	}
	return (0);
}
