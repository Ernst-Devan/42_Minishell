/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:17:18 by njooris           #+#    #+#             */
/*   Updated: 2025/05/16 13:00:27 by njooris          ###   ########.fr       */
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
	return (NULL);
}

int	cd(t_cmd cmd, char ***env)
{
	int		check;
	char	*pwd;
	char	*pwd2;
	char	*new_pwd;
	char	*old_pwd;
	char	*temp;

	if (!cmd.args[1])
	{
		temp = get_home(*env);
		if (!temp)
		{
			write(2, "HOME not set\n", ft_strlen("HOME not set \n"));
			return (1);
		}
	}
	pwd2 = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", pwd2);
	free(pwd2);
	old_pwd = ft_strjoin("OLD", pwd);
	if (set_pwd(old_pwd, env))
		return (1);
	if (cmd.args[1])
	{
		new_pwd = build_pwd(pwd, cmd.args[1]);
		if (!new_pwd[4])
			return (0);
		check = chdir(&new_pwd[4]);
		if (check != 0)
			return (perror("Error in chdir"), 1);
	}
	else
	{
		check = chdir(&temp[5]);
		if (check != 0)
			return (perror("Error in chdir2"), 1);
		new_pwd = ft_strjoin("PWD=", &temp[5]);
	}
	if (set_pwd(new_pwd, env))
		return (1);
	return (0);
}
