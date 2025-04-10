
#ifndef PARSING_H 
# define PARSING_H

#include <stdlib.h>

# define NAME_MAX 255

typedef struct s_shell {
    size_t	status;
    char	**env;
	int		nb_cmd;
    int		error_code;
} t_shell;

typedef struct s_cmd {
	size_t	type;
	char	*path;
	char	**args;
} t_cmd;

typedef struct s_table
{
	int		in;
	int		out;
	t_cmd	*cmds;
} t_table;


//Parsing.c 
t_table		parsing(char **env);

//Init.c

//Env.c
char		*find_env(char *str, char **env);

//Utils.c 
void		display_table(t_table table);
int			count_lstr(char **list_str);

//Lexer.c
size_t		check_delimter(char c);
char		*lexer(char *input, char **env);
int			ft_strlen_c(char *str, const char *delimiter);

#endif
