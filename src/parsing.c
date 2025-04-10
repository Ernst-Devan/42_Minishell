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
        list_cmds++;
        i++;
    }
}

int	open_redirection(t_table *table, char in[NAME_MAX], char out[NAME_MAX])
{
	if (in[0])
		table->in = open(in, O_RDONLY);
	else
		table->in = 0;
	if (out[0])
		table->out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		table->out = 1;
	if (table->out < 0)
			return(1);
	return (0);
}

char	*insert_redirection(t_table *table, char *input)
{
	char	*buffer;
	char	in[NAME_MAX];
	char	out[NAME_MAX];
	int		count;
	int		i;

	ft_strlcpy(in, "\0", 1);
	ft_strlcpy(out, "\0", 1);
	buffer = malloc(ft_strlen(input) * sizeof(char));
	i = 0;
	while (*input)
	{
		if (*input == '<' || *input == '>')
		{
			count = ft_strlen_c(input, ": ");
			if (*input == '<')
			{
				ft_strlcpy(in, input + 1, count);
			}
			else if (*input == '>')
			{
				ft_strlcpy(out, input + 1, count);
			}
			input += count;
		}
		buffer[i] = *input;
		i++;
		input++;
	}
	open_redirection(table, in, out);
	buffer[i] = '\0';
	return (buffer);
}

// Do VECTOR for char *
// NOT JUST SPACE BE CAREFUL TO ALL delimiter

char	**tokenisation(char *input)
{
	char **splited_cmds;

	splited_cmds = ft_split(input, '|');
	return (splited_cmds);
}


t_table parsing(char **env)
{
	t_table	table;
    t_cmd	*cmd;
	char	*path;
    char	*input;

	table = (t_table){0};
	cmd = 0;

    input = readline("-> ");

    // Lexer return a str great writed
    input = lexer(input, env);
    
	path = find_env("PATH=", env);
    // Tokenisation splited the lexer string to token
	input = insert_redirection(&table, input);
	insert_cmds(&cmd, tokenisation(input), path);
	table.cmds = cmd;	
	free(input);
    return (table);
}
