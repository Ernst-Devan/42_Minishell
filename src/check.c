// ADD THE HEADER 

#include "parsing.h"
#include <limits.h>
#include <stddef.h>
#include "libft.h"
#include <threads.h>
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


#include <stdio.h>
char  *check_command(char *path, char *command)
{
	char    **splited_path;
	char    temp_path[PATH_MAX];
	char    *final_path;
	int		i;

	i = 0;
	if (command == NULL)
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
	return (NULL);
}

char	*valid_command(char *path, char *command, size_t *type)
{
	char *temp;

	if (check_bultin(command))
	{
		*type = 1;
		return (command);
	}
	temp = check_command(path, command);
	if (temp)
	{
		*type = 0;
		return(temp);
	}
	*type = 3;
	return (command);
}


