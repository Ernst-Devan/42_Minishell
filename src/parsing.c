#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "parsing.h"
//! Secure the env if null (env -i)

void    display_split(char **str)
{
    while (*str != NULL)
    {
        ft_printf("%s\n", *str);
        str++;  
    }
}

char *get_path(char **env)
{
    while (*env != NULL)
    {
        if (ft_strncmp("PATH=", *env, 5) == 0)
            return (*env + 5);
        env++;
    }
    return (NULL);
}

char  *check_command(char *path, char *command)
{
    char    **splited_path;
    char    temp_path[PATH_MAX];
    char    *final_path;

    splited_path = ft_split(path, ':');
    while(*splited_path != NULL)
    {
        ft_strlcpy(temp_path, *splited_path, ft_strlen(*splited_path) + 1);
        ft_strlcat(temp_path, "/", ft_strlen(temp_path) + 2);
        ft_strlcat(temp_path, command, ft_strlen(temp_path) + ft_strlen(command) + 1);
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

void    error_message(int error_code)
{
    if (error_code == 1)
    {
        ft_printf("Unknow Command\n");
    }
}

t_command parsing(char **env)
{
    char *path;
    char *buffer;
    t_command   command;

    path = get_path(env);
    buffer = readline("-> ");
    command.args = ft_split(buffer, ' ');
    command.path = check_command(path, command.args[0]);
    if (!command.path)
    {
        command.path = command.args[0];
        command.args++;
    }
    return (command);
    free(buffer);
}
