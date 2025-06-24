/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:00:59 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 17:28:17 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "exec.h"
#include "libft.h"
#include "env_manage.h"

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
	i = -1;
	while (++i < nb_row)
	{
		temp[i] = ft_strdup((*env)[i]);
		if (!temp[i])
			return (free_lstr(temp), 1);
	}
	free_lstr(*env);
	temp[i] = ft_strdup(data);
	if (!temp[i])
	{
		*env = NULL;
		return (free_lstr(temp), 1);
	}
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

int	check_name(char	*str)
{
	int	i;

	i = 0;
	if (str && str[0])
	{
		if (!ft_isalpha(str[0]) && str[i] != '_')
			return (1);
	}
	while (str && str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}
