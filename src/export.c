/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:52:31 by njooris           #+#    #+#             */
/*   Updated: 2025/05/23 15:23:01 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"
#include "env_manage.h"
#include "builtins.h"

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
		if (ft_strncmp(env[i], str, len) == 0 && (env[i][len] == '=' || !env[i][len]))
			return (i);
		i++;
	}
	return (-1);
}

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
		{
			free_lstr(temp);
			return (1);
		}
		i++;
	}
	free_lstr(*env);
	temp[i] = data;
	*env = temp;
	return (0);
}

int	edit_variable_env(char ***env, char *data)
{
	int	i;

	i = find_env_variable(*env, data);
	free((*env)[i]);
	(*env)[i] = data;
	return (0);
}

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

char	*find_n(char **env, int nb)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (count_bigger_than(env[i], env) == nb)
			return env[i];
		i++;
	}
	return (env[i]);
}

void	export_without_param(char **env)
{
	int	i;
	int	j;
	int	check;
	char	*str;

	i = 0;
	while (env[i])
	{
		check = 0;
		j = 0;
		if (ft_strncmp(find_n(env, i), "_=", 2) != 0)
		{
			str = find_n(env, i);
	 		write(1, "declare -x ", ft_strlen("declare -x "));
			while (str[j])
			{
				write(1, &str[j], 1);
				if (str[j] == '=')
				{
					write(1, "\"", 1);
					check = 1;
				}
				if (!str[j + 1] && check == 1)\
				{
					write(1, "\"", 1);
				}
				j++;
			}
			write(1, "\n", 1);
		}
	 	i++;
	}
}

int	export(t_cmd cmd, char ***env)
{
	int	len;
	int	i;
	int	check;
	int	check2;

	check2 = 0;
	if (!cmd.args[1])
	{
		export_without_param(*env);
		return (0);
	}
	i = 1;
	while (cmd.args[i])
	{
		if (cmd.args[i] && !ft_isalpha(cmd.args[i][0]))
		{
			check2++;
			if (check2 == 1)
				printf("Bad param(s)\n");
		}
		else
		{
			len = var_env_len(cmd.args[i]);
			check = find_env_variable(*env, cmd.args[i]);
			if (check == -1)
			{
				if (add_variable_env(env, cmd.args[i]))
					return (1);
			}
			else if (cmd.args[i][len] == '=')
				edit_variable_env(env, cmd.args[i]);
		}
		i++;
	}
	return (0);
}
