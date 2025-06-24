/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:52:31 by njooris           #+#    #+#             */
/*   Updated: 2025/06/23 16:23:34 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "exec.h"
#include "libft.h"
#include "env_manage.h"

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
