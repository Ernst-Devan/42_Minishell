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
#include <limits.h>
#include <stddef.h>
#include "libft.h"
#include <threads.h>
#include <time.h>
#include <unistd.h>

size_t check_bultin(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command) + 4))
		return(1);
	else if (!ft_strncmp(command, "cd", ft_strlen(command) + 2))
		return(1);
	else if (!ft_strncmp(command, "pwd", ft_strlen(command) + 3))
		return(1);
	else if (!ft_strncmp(command, "export", ft_strlen(command) + 6))
		return(1);
	else if (!ft_strncmp(command, "unset", ft_strlen(command) + 5))
		return(1);
	else if (!ft_strncmp(command, "env", ft_strlen(command) + 3))
		return(1);
	else if (!ft_strncmp(command, "exit", ft_strlen(command)+ 4))
		return(1);
return(0);
}

char  *check_command(char *path, char *command)
{
	char    **splited_path;
	char    temp_path[PATH_MAX];
	char    *final_path;
	int		i;

	i = 0;
	if (command == NULL)
		return(NULL);
	if (!path)
		return(NULL);
	splited_path = ft_split(path, ':');
	if (!splited_path)
		return(NULL);
	while(splited_path[i] != NULL)
	{
		ft_strlcpy(temp_path, splited_path[i], PATH_MAX);
		ft_strlcat(temp_path, "/", PATH_MAX);
		ft_strlcat(temp_path, command, PATH_MAX);
		if (!access(temp_path, X_OK | F_OK))
		{
			final_path = ft_strdup(temp_path);
			free_lstr(splited_path);
			if (!final_path)
				return (NULL); 
			return (final_path);
		}
		i++;
	}
	free_lstr(splited_path);
	return (NULL);
}

char	*check_relative_path(char *command)
{
	// check ./ or path
	if (count_characters(command, "/") >= 1)
	{
		if (command[0] == '.' && command[1] == '/')
		{
			if (!access(command, X_OK | F_OK))
				return (command);
		}
		if (!access(command, X_OK | F_OK))
			return (command);
	}
	return (NULL);
}

char	*valid_command(char *path, char *command, size_t *type)
{
	char	*temp;
	char	*cpy_command;

	cpy_command = ft_strdup(command);
	if (!cpy_command)
		return (NULL);
	if (count_characters(cpy_command, "/") >= 1)
	{
		*type = 0;
		return(cpy_command);
	}
	if (check_bultin(cpy_command))
	{
		*type = 1;
		return (cpy_command);
	}
	temp = check_command(path, cpy_command);
	if (temp)
	{
		*type = 0;
		free(cpy_command);
		return(temp);
	}
	*type = 3;
	return (cpy_command);
}


