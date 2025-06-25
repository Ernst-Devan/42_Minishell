/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:27:36 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 11:27:40 by njooris          ###   ########.fr       */
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
	char	*buffer;
	char	*cpy_command;

	cpy_command = ft_strdup(command);
	if (!cpy_command || ft_strlen(cpy_command) == 0)
	{
		free(cpy_command);
		return (NULL);
	}
	if (count_chars(cpy_command, "/") >= 1)
	{
		*type = COMMAND;
		return (cpy_command);
	}
	else if (check_bultin(cpy_command))
	{
		*type = BUILTIN;
		return (cpy_command);
	}
	buffer = check_command(path, cpy_command);
	if (buffer)
	{
		*type = COMMAND;
		free(cpy_command);
		return (buffer);
	}
	return (cpy_command);
}
