
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

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

//int check_bultins();

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


char **parsing(char **env)
{
    char *path;
    char **table_command = NULL;
    char *buffer;
    char *command_path;

    path = get_path(env);
    while (1)
    {
        buffer = readline("-> ");
        command_path = check_command(path, buffer);
        if (!command_path)
            error_message(1);
        else
            ft_printf("%s\n", command_path);
        free(buffer);
    }
    return (table_command);
}
