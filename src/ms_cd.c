/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:17:18 by njooris           #+#    #+#             */
/*   Updated: 2025/04/28 11:17:35 by njooris          ###   ########.fr       */
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
char	*remove_consecutiv_slash(char *path)
{
	int	i;
	int	j;
	int	len;
	char	*new_path;

	i = 0;
	j = 0;
	len = 0;
	while (path[i])
	{
		while (path[i] == '/' && path[i + 1] == '/')
			i++;
		i++;
		len++;
	}
	i = 0;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
		return (NULL);
	while (path[i] && j < len)
	{
		new_path[j] = path[i];
		if (path[i] == '/' && path[i + 1] == '/')
		{
			while (path[i] == '/' && path[i + 1] == '/')
				i++;
		}
		i++;
		j++;
	}
	new_path[len] = '\0';
	return (new_path);
}

char	*remove_dot_slash(char *path)
{
	int	i;
	int	j;
	int	len;
	char	*new_path;

	i = 0;
	j = 0;
	len = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '/')
			i+=2;
		i++;
		len++;
	}
	if (path[i - 1] == '.')
	{
		len--;
		printf("len : %d\n", len);
	}
	i = 0;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
	 	return (NULL);
	while (path[i] && j < len)
	{
	 	if (path[i] == '.' && path[i + 1] == '/')
	 	{
	 		while (path[i] == '.' && path[i + 1] == '/')
	 			i += 2;
	 	}
		else
		{
			new_path[j] = path[i];
			i++;
	 		j++;
		}
	}
	new_path[len] = '\0';
	return (new_path);
}

char	*strljoin(char const *s1, char const *s2, int len)
{
	char	*str;
	size_t	i;

	str = malloc((len + ft_strlen(s2)) + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (*s1 && i < len)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*remove_if_dotdot(char *path)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.')
		{
			j = i - 2;
			while (path[j] && path[j] != '/')
				j--;
			temp = path;
			path = strljoin(path, &path[i + 2], j);
			free (temp);
			i = -1;
		}
		i++;
	}
	return (path);
}

char	*build_pwd(char *pwd, char *path)
{
	if (path[0] == '/')
	{
		pwd = NULL;
		ft_strlcpy(pwd, path, ft_strlen(path) + 1);
		return (pwd);
	}
	if (pwd[ft_strlen(pwd) - 1] != '/' && path[0] != '/')
		pwd = ft_strjoin(pwd, "/");
	pwd = ft_strjoin(pwd, path);
	pwd = remove_consecutiv_slash(pwd);
	pwd = remove_if_dotdot(pwd);
	pwd = remove_dot_slash(pwd);

	if (!pwd)
		return (NULL);
	// supprimer le last / si il y est
	// proteger tous les malloc
	return (pwd);
}

int	set_pwd(char *pwd, char ***env)
{
	char	*new_pwd;
	int		check;

	// Donner une chaine pwd construite comme ca : PWD=aoksdoaskdoask\0
	check = find_env_variable(*env, pwd);
	if (check == -1)
		return (add_variable_env(env, pwd));
	edit_variable_env(env, pwd);
	return (0);
}

int	cd(t_cmd cmd, char ***env)
{
	int	i;
	char *pwd;
	char *new_pwd;
	char *old_pwd;

	pwd = get_pwd(*env);
	old_pwd = ft_strjoin("OLD", pwd);
	if (set_pwd(old_pwd, env))
		return (1);
	if (chdir(cmd.args[1]))
	{
		perror("Error in chdir");
		return (1);
	}
	new_pwd = build_pwd(pwd, cmd.args[1]);
	if (set_pwd(new_pwd, env))
		return (1);
	return (0);
}