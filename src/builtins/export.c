/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:52:31 by njooris           #+#    #+#             */
/*   Updated: 2025/06/26 13:03:20 by njooris          ###   ########.fr       */
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
			return (free_lstr(temp));
	}
	free_lstr(*env);
	temp[i] = ft_strdup(data);
	if (!temp[i])
		return (free_lstr(temp));
	*env = temp;
	return (0);
}

int	export_with_param(t_cmd cmd, char ***env)
{
	int	check;
	int	check2;
	int	i;

	i = 0;
	check2 = 0;
	while (cmd.args[++i])
	{
		if (cmd.args[i] && check_name(cmd.args[i]))
		{
			if (++check2 == 1)
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
	return (check2 > 0);
}

int	export(t_cmd cmd, char ***env)
{
	int	i;
	int	check2;

	check2 = 0;
	if (!cmd.args[1])
	{
		export_without_param(*env);
		return (0);
	}
	i = 0;
	return (export_with_param(cmd, env) == 1);
}
