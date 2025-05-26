/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:54:25 by njooris           #+#    #+#             */
/*   Updated: 2025/05/26 11:22:57 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"
#include "env_manage.h"

int	del_env_var(char ***env, char *str, char **new_env)
{
	int		i;
	int		j;
	char	**env2;

	i = 0;
	j = 0;
	env2 = *env;
	while ((*env)[i])
	{
		if (ft_strncmp(str, (*env)[i], ft_strlen(str) - 1) == 0)
		{
			free ((*env)[i]);
			i++;
		}
		new_env[j] = env2[i];
		if ((*env)[i])
		{
			i++;
			j++;
		}
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	unset(t_cmd cmd, char ***env)
{
	int		i;
	int		check;
	char	**new_env;
	char	*str;

	if (!cmd.args[1])
	{
		printf("unset need param\n");
		return (1);
	}
	new_env = NULL;
	i = 1;
	while (cmd.args[i])
	{
		str = ft_strjoin(cmd.args[i], "=");
		if (!str)
			return (1);
		check = find_env_variable(*env, str);
		if (check != -1)
		{
			new_env = malloc(sizeof(char *) * (size_of_env(*env)));
			if (!new_env)
			{
				free(str);
				return (1);
			}
			del_env_var(env, str, new_env);
		}
		i++;
	}
	return (0);
}
