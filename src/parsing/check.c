/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:27:36 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 18:22:25 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

size_t	check_bultin(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command) + 4))
		return (1);
	else if (!ft_strncmp(command, "cd", ft_strlen(command) + 2))
		return (1);
	else if (!ft_strncmp(command, "pwd", ft_strlen(command) + 3))
		return (1);
	else if (!ft_strncmp(command, "export", ft_strlen(command) + 6))
		return (1);
	else if (!ft_strncmp(command, "unset", ft_strlen(command) + 5))
		return (1);
	else if (!ft_strncmp(command, "env", ft_strlen(command) + 3))
		return (1);
	else if (!ft_strncmp(command, "exit", ft_strlen(command)+ 4))
		return (1);
	return (0);
}

char	*check_command(char *path, char *command)
{
	char	**splited_path;
	char	temp_path[PATH_MAX];
	char	*final_path;
	int		i;

	i = -1;
	if (command == NULL || !path)
		return (NULL);
	splited_path = ft_split(path, ':');
	while (splited_path && splited_path[++i])
	{
		ft_strlcpy(temp_path, splited_path[i], PATH_MAX);
		ft_strlcat(temp_path, "/", PATH_MAX);
		ft_strlcat(temp_path, command, PATH_MAX);
		if (!access(temp_path, X_OK | F_OK))
		{
			final_path = ft_strdup(temp_path);
			free_lstr(splited_path);
			if (final_path)
				return (final_path);
		}
	}
	free_lstr(splited_path);
	return (NULL);
}

char	*valid_command(char *path, char *command, size_t *type)
{
	char	*arr[2];

	if (!command || !ft_strlen(command))
		return (NULL);
	arr[0] = ft_strdup(command);
	if (!arr[0])
		return (NULL);
	if (count_chars(arr[0], "/") >= 1)
	{
		*type = COMMAND;
		return (arr[0]);
	}
	else if (check_bultin(arr[0]))
	{
		*type = BUILTIN;
		return (arr[0]);
	}
	arr[1] = check_command(path, arr[0]);
	if (arr[1])
	{
		*type = COMMAND;
		free(arr[0]);
		return (arr[1]);
	}
	return (arr[0]);
}
