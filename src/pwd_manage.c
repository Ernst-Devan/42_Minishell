/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:12:48 by njooris           #+#    #+#             */
/*   Updated: 2025/05/05 11:13:50 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

char	*update_pwd(char *pwd)
{
	char	*new_pwd;
	char	*pwd_cpy;

	ft_strlcpy(pwd_cpy, pwd, ft_strlen(pwd) + 1);
	if (!pwd_cpy)
		return (NULL);
	return (pwd_cpy);
}

char	*get_pwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (env[i]);
}

char	*build_pwd(char *pwd, char *path)
{
	
	if (path[0] == '/')
		pwd = ft_strjoin("PWD=", path);
	else
	{
		if (pwd[ft_strlen(pwd) - 1] != '/' && path[0] != '/')
			pwd = ft_strjoin(pwd, "/");
		pwd = ft_strjoin(pwd, path);
	}
	pwd = remove_consecutiv_slash(pwd);
	pwd = remove_if_dotdot(pwd);
	pwd = remove_dot_slash(pwd);
	if(ft_strlen(pwd) == 4)
	{
		free(pwd);
		pwd = ft_strjoin("PWD=", "/");
	}
	if (!pwd)
		return (NULL);
	// proteger tous les malloc
	return (pwd);
}

int	set_pwd(char *pwd, char ***env)
{
	char	*new_pwd;
	int		check;

	check = find_env_variable(*env, pwd);
	if (check == -1)
		return (add_variable_env(env, pwd));
	edit_variable_env(env, pwd);
	return (0);
}