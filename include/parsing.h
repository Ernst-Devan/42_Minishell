
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


//Redirection.c
int		open_redirection(t_table *table, char in[NAME_MAX], char out[NAME_MAX]);
char	*insert_redirection(t_table *table, char *input);

//Parsing.c 
t_table		parsing(char **env);

//Init.c
void	init_cmd(t_cmd *cmd, int nb_cmd);
int		init_table(t_table *table, int nb_cmd);


//Free.c
void	free_lstr(char **lstr);
void	free_cmds(t_cmd *cmd);
void	free_table(t_table table);

//Env.c
char		*find_env(char *str, char **env);

//Utils.c
int			ft_strlen_c(char *str, const char *delimiter);
size_t		check_delimiter(char c);
void		display_lstr(char **lstr);
void		display_table(t_table table);
int			count_character(char *s, char c);
int			count_lstr(char **list_str);

//Check.c
char	*check_command(char *path, char *command);

//Lexer.c
char		*lexer(char *input, char **env);

#endif