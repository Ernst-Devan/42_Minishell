#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "parsing.h"

// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls

char  *check_command(char *path, char *command)
{
    char    **splited_path;
    char    temp_path[PATH_MAX];
    char    *final_path;


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

void	display_lstr(char **lstr)
{
	while(*lstr)
	{
		ft_printf("%s\n", *lstr);
		lstr++;
	}
	ft_printf("\n");
}



void insert_cmds(t_cmd **cmd, char **list_cmds, char *path)
{
    char **args;
	char *path_command;
	int count;
    int i;
	
    i = 0;
    count = count_lstr(list_cmds);
	(*cmd) = malloc((count + 1)* sizeof(t_cmd));
	(*cmd)[count] = (t_cmd){0};
	// Protect malloc

	while (*list_cmds != NULL)
    {
        args = ft_split(*list_cmds, ':');
		path_command = check_command(path, args[0]);
		if (!path_command)
		{
			path_command  = args[0];
		}
        (*cmd)[i].type = 0;
        (*cmd)[i].path = path_command;
        (*cmd)[i].args = args;
		(*cmd)[i].in = 0;
		(*cmd)[i].out = 0;
        list_cmds++;
        i++;
    }
}

// Do VECTOR for char *
// NOT JUST SPACE BE CAREFUL TO ALL delimiter

char	**tokenisation(char *input)
{
	char **splited_cmds;

	splited_cmds = ft_split(input, '|');
	return (splited_cmds);
}


t_cmd *parsing(char **env)
{
    t_cmd   *cmd;
	char	*path;
    char    *input;

	cmd = 0;
    input = readline("-> ");

    // Lexer return a str great writed
    input = lexer(input, env);
    
	path = find_env("PATH=", env);
    // Tokenisation splited the lexer string to token
	insert_cmds(&cmd, tokenisation(input), path);
	free(input);
    return (cmd);
}
