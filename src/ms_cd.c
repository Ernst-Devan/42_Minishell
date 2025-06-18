/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:17:18 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 13:53:44 by njooris          ###   ########.fr       */
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

int	manage_old_pwd(char *pwd, char ***env)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLD", pwd);
	if (!old_pwd)
	{
		free(pwd);
		return (write(2, "fail on cd\n", 11), 1);
	}
	if (set_pwd(old_pwd, env))
	{
		free(old_pwd);
		return (1);
	}
	free(old_pwd);
	return (0);
}

int	cd_with_arg(char ***env, char *pwd, char *arg)
{
	char	*new_pwd;

	new_pwd = build_pwd(pwd, arg);
	if (!new_pwd)
		return (1);
	if (!new_pwd[4])
	{
		free(new_pwd);
		return (0);
	}
	if (chdir(&new_pwd[4]) != 0)
	{
		free(new_pwd);
		return (perror("Error in chdir"), 1);
	}
	if (set_pwd(new_pwd, env))
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

int	set_cd(char ***env, char *pwd, t_cmd cmd, char *temp)
{
	char	*new_pwd;

	if (manage_old_pwd(pwd, env))
		return (1);
	if (cmd.args[1])
		return (cd_with_arg(env, pwd, cmd.args[1]));
	free(pwd);
	new_pwd = ft_strjoin("PWD=", &temp[5]);
	if (chdir(&temp[5]) != 0 || !new_pwd)
		return (write(2, "fail on cd\n", 11), 1);
	if (set_pwd(new_pwd, env))
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

int	cd(t_cmd cmd, char ***env)
{
	char	*pwd;
	char	*new_pwd;
	char	*temp;

	if (!cmd.args[1])
	{
		temp = get_home(*env);
		if (!temp)
			return (write(2, "HOME not set\n", 13), 1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (write(2, "fail on cd\n", 11), 1);
	pwd = ft_strjoin("PWD=", new_pwd);
	if (!pwd)
		return (write(2, "fail on cd\n", 11), 1);
	free(new_pwd);
	return (set_cd(env, pwd, cmd, temp));
}
