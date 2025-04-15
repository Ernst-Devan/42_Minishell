// ADD THE HEADER 

#include "parsing.h"
#include <limits.h>
#include <stdio.h>
#include "libft.h"
#include <unistd.h>

char  *check_command(char *path, char *command)
{
    char    **splited_path;
    char    temp_path[PATH_MAX];
    char    *final_path;

	if (command == NULL)
		return(NULL);
    splited_path = ft_split(path, ':');
    while(*splited_path != NULL)
    {
        ft_strlcpy(temp_path, *splited_path, PATH_MAX);
        ft_strlcat(temp_path, "/", PATH_MAX);
        ft_strlcat(temp_path, command, PATH_MAX);
        if (!access(temp_path, X_OK | F_OK))
        {
            final_path = ft_strdup(temp_path);
            if (!final_path)
                return (NULL);
			return (final_path);
		}
		splited_path++;
	}
	return (NULL);
}
