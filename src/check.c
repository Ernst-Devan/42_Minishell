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

//Maybe decale here the pointer to skip the redirection but problem for free the char **

char	*ft_ignore_str(char *str, char *ignore)
{
	char	*cpy_str;
	char	*temp;
	size_t	i;

	cpy_str = str;
	i = 0;
	temp = malloc(ft_strlen(str) + 1);
	while (*cpy_str)
	{
		if (*cpy_str == *ignore)
		{
			if (!ft_strncmp(cpy_str, ignore, ft_strlen(ignore)))
				cpy_str += ft_strlen(ignore);
		}
		if (!*cpy_str)
			break;
		temp[i] = *cpy_str;
		i++;
		cpy_str++;
	}
	temp[i] = '\0';
	return (temp);
}


void manage_redirection(t_cmd *cmds, char **split_cmd)
{
	size_t	i;
	size_t	j;
	char	in[NAME_MAX];
	char	out[NAME_MAX];

	i = 0;
	j = 0;
	in[0] = '\0';
	out[0] = '\0';
	while (split_cmd[i])
	{
		while (split_cmd[i][j])
		{
			if (split_cmd[i][j] == '<')
			{
				ft_strccpy(in, &split_cmd[i][j + 2], ':');
				split_cmd[i] = ft_ignore_str(split_cmd[i], in);
				open_in(&cmds[i],in);
				ft_strlcpy(in, "\0", NAME_MAX);
			}
			else if (split_cmd[i][j] == '>')
			{
				ft_strccpy(out, &split_cmd[i][j + 2], ':');
				split_cmd[i] = ft_ignore_str(split_cmd[i], out);
				open_out(&cmds[i],out);
				ft_strlcpy(out, "\0", NAME_MAX);
			}
			j++;
		}
		split_cmd[i] = ft_ignore_str(split_cmd[i], "<\0");
		split_cmd[i] = ft_ignore_str(split_cmd[i], ">\0");
		j = 0;
		i++;
	}
}
