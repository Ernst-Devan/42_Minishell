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
// MANAGE IF NAME FILE ARE TWO LONG

int insert_cmds(t_cmd **cmd, char **list_cmds, char *path)
{
	int		res;
	int		i;
	int		count;
	char	**args;
	char	*path_command;

	i = 0;
	res = 0;
	count = count_lstr(list_cmds);
	(*cmd) = malloc((count + 1) * sizeof(t_cmd));
	//Protect Malloc 
	if (!*cmd)
		res = 1;
	(*cmd)[count] = (t_cmd){0};

	while (*list_cmds != NULL)
    {
        args = ft_split(*list_cmds, ':');
		if (!args)
			res = 1;
		(*cmd)[i].type = 0;
		path_command = check_command(path, args[0]);
		if (!path_command)
		{
			(*cmd)[i].type = 1;
			path_command  = args[0];
		}
        (*cmd)[i].path = path_command;
        (*cmd)[i].args = args;
        list_cmds++;
        i++;
    }
	return(res);
}

// NOT JUST SPACE BE CAREFUL TO ALL delimiter
char	**tokenisation(char *input)
{
	int		res;
	char	**splited_cmds;

	res = 0;
	splited_cmds = ft_split(input, '|');
	if (!splited_cmds)
		res = 1;
	return (splited_cmds);
}

t_table parsing(char **env)
{
	t_table	table;
    char	*input;
	char	**splited_cmds;

	input = readline("-> ");
	if (!input)
	{
		exit(1);
	}

    // Lexer return a str great writed
	input = lexer(input, env);
    // Tokenisation splited the lexer string to token
	init_table(&table, count_character(input, '|'));
	input = insert_redirection(&table, input);
	splited_cmds = tokenisation(input);
	insert_cmds(&table.cmds, splited_cmds, find_env("PATH=", env));

	free_lstr(splited_cmds);
	free(input);
	return (table);
}
