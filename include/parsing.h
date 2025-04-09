
#ifndef PARSING_H 
# define PARSING_H

#include <stdlib.h>

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
    int		in;
    int		out;
} t_cmd;

//Parsing.c 
t_cmd		*parsing(char **env);

//Init.c

//Env.c
char		*find_env(char *str, char **env);

//Utils.c 
void		display_table(t_cmd *cmds);
int			count_lstr(char **list_str);

//Lexer.c
size_t		check_delimter(char c);
char		*lexer(char *input, char **env);

#endif
