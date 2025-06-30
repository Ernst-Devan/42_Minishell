/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:12:48 by njooris           #+#    #+#             */
/*   Updated: 2025/06/30 17:00:29 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*update_pwd(char *pwd)
{
	char	*pwd_cpy;

	pwd_cpy = NULL;
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

char	*pwd_manage(char *pwd)
{
	char	*temp;

	temp = pwd;
	pwd = remove_consecutiv_slash(pwd);
	free(temp);
	if (!pwd)
		return (NULL);
	pwd = remove_dot_slash(pwd);
	if (!pwd)
		return (NULL);
	pwd = remove_if_dotdot(pwd);
	if (!pwd)
		return (NULL);
	if (ft_strlen(pwd) > 0 && pwd[ft_strlen(pwd) - 1] == '/')
		pwd[ft_strlen(pwd) - 1] = '\0';
	if (ft_strlen(pwd) == 4)
	{
		free(pwd);
		pwd = ft_strjoin("PWD=", "/");
		if (!pwd)
			return (NULL);
	}
	return (pwd);
}

char	*build_pwd(char *pwd, char *path)
{
	char	*temp;

	if (path[0] == '/')
	{
		free(pwd);
		pwd = ft_strjoin("PWD=", path);
	}
	else
	{
		if (pwd[ft_strlen(pwd) - 1] != '/' && path[0] != '/')
		{
			temp = pwd;
			pwd = ft_strjoin(pwd, "/");
			free(temp);
		}
		temp = pwd;
		pwd = ft_strjoin(pwd, path);
		free(temp);
	}
	if (!pwd)
		return (NULL);
	pwd = pwd_manage(pwd);
	return (pwd);
}

int	set_pwd(char *pwd, char ***env)
{
	int		check;

	check = find_env_variable(*env, pwd);
	if (check == -1)
		return (add_variable_env(env, pwd));
	edit_variable_env(env, pwd);
	return (0);
}
