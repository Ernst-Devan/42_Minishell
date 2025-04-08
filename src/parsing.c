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

//! Define better delimiter

size_t check_delimiter(char c)
{
    char delimiter[7] = {" <>|-&\0"};
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (c == delimiter[i])
            return (1);
        i++;
    }
    return (0);
}

int count_cmds(char **splited_cmds)
{
    int i;

    i = 0;
    while (*splited_cmds)
    {
        i++;
        splited_cmds++;
    }
    return (i);
}
// Manage space before and after the input 
// Make a better allocation for the buffer

char    **lexeur(char *input)
{
    char *buffer;
    char **splited_cmds;
    int i;
    int a;

    i = 0;
    a = 0;
    buffer = malloc((ft_strlen(input) * 2) * sizeof(char));
    while (input[a])
    {
        if (check_delimiter(input[a]) == 1)
        {
            if (buffer[i - 1] == ':' && input[a] == ' ')
                a++;
            else
            {
                if (buffer[i - 1] != ':')
                {
                    buffer[i] = ':';
                    i++;
                }
                if (input[a] != ' ')
                {
                    buffer[i] = input[a];
                    i++;
                    a++;
                }
            }
        }
        else 
        {
            buffer[i] = input[a];
            i++;
            a++;
        }
    }
    buffer[i] = '\0';
    splited_cmds = ft_split(buffer, '|');
    free(buffer);
    return (splited_cmds);
}


t_command *insert_table(t_command *cmds, char **list_cmds)
{
    char **args;
    int i;
    i = 0;
    while (*list_cmds != NULL)
    {
        args = ft_split(*list_cmds, ':');
        cmds[i].type = 0;
        cmds[i].cmd = args[0];
        cmds[i].args = args;
        list_cmds++;
        i++;
    }
    return (cmds);
}

void    display_table(t_command *cmds, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        ft_printf("type : %d\n", cmds[i].type);
        ft_printf("cmd  : %s\n", cmds[i].cmd);
        ft_printf("args : ");
        while (*cmds[i].args != NULL)
        {
            ft_printf("%s ", *cmds[i].args);
            cmds[i].args++;
        }
        ft_printf("\n\n");
        i++;
    }
}

t_command *parsing(char **env)
{
    char **splited_cmds; 
    char *path;
    char *input;
    int count;
    t_command   *command;
    t_status    status;

    command = (t_command *){0};
    status = (t_status){0};

    path = get_path(env);
    input = readline("-> ");
    splited_cmds = lexeur(input);
    count = count_cmds(splited_cmds);
    command = malloc(count * sizeof(t_command));
    insert_table(command, splited_cmds);
    return (command);
    free(input);
}
