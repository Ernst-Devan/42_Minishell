/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:17:18 by njooris           #+#    #+#             */
/*   Updated: 2025/05/05 11:19:57 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

char	*get_home(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("HOME=", env[i], 5) == 0)
			return (env[i]);
		i++;
	}
	return (env[i]);
}

int	cd(t_cmd cmd, char ***env)
{
	int		check;
	char	*pwd;
	char	*new_pwd;
	char	*old_pwd;
	char	*temp;

	pwd = get_pwd(*env);
	old_pwd = ft_strjoin("OLD", pwd);
	if (set_pwd(old_pwd, env))
		return (1);
	if (cmd.args[1])
	{
		check = chdir(cmd.args[1]);
		if (check != 0)
			return (perror("Error in chdir"), 1);
		new_pwd = build_pwd(pwd, cmd.args[1]);
	}
	else
	{
		temp = get_home(*env);
		new_pwd = ft_strjoin("PWD=", &temp[5]);
	}
	if (set_pwd(new_pwd, env))
		return (1);
	return (0);
}
