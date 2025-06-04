
#ifndef PARSING_H
#define PARSING_H

#include <stddef.h>
#include <stdlib.h>

#define NAME_MAX 255
#define ENV_MAX 32760
#define DELIMITER " -<>|"
#define SEPARATOR '\x1F'
#define SEPARATOR2 "\x1F"

typedef struct s_shell {
  size_t	status;
  char		**env;
  int		nb_cmd;
  int		error_code;
} t_shell;

typedef struct s_cmd {
  size_t	type;
  char		*path;
  char		**args;
  char		*str_in;
  char		*str_out;
  int		in;
  int		out;
}	t_cmd;

typedef struct s_lst_child{
	int					pid;
	struct s_lst_child	*next;
}	t_lst_child;

typedef struct s_table {
  t_cmd		*cmds;
  size_t	cmd_len;
}	t_table;

typedef struct s_expand{
	size_t	i;
	size_t	j;
	size_t	alloc;
	char	*buffer;
}	t_expand;

// Redirection.command
void	manage_redirection(t_cmd **cmd, char **split_cmd);
char	**skip_redirection(char **split_cmd);

char	*remove_quote(char *str);

// Parsing.c
t_table	parsing(t_shell *shell);

// Init.c
void	init_cmd(t_cmd *cmd, int nb_cmd);
int		init_table(t_table *table, int nb_cmd);

//Quotes.c
char	**remove_quotes(char **splited_cmd);

// Free.c
void	free_lstr(char **lstr);
void	free_cmds(t_table table);
void	free_table(t_table table);

// Env.c
char *find_env(char *str, char **env);

// Command_split.c
size_t	count_split(char *input, char c);
size_t	nb_letter(char *input, char c);
char	**split_cmd(char *input, char c);

// Utils.c
int		ft_strlen_c(char *str, char delimiter);
size_t	check_delimiter(char c, char *delimiter);
void	display_lstr(char **lstr);
void	display_table(t_table table);
size_t	count_characters(char *s, char *cs);
int		count_lstr(char **list_str);
size_t	ft_strccpy(char *dest, const char *src, char c);
size_t	lstrlen(char **lstr);
char	*skip_characters(char *input, char c);
size_t	ft_strccat(char *dest, char *src, char c);

// Expand.c
char	*manage_expand(char *input, t_shell shell);
size_t	init_expand(t_expand *expand, char *input, t_shell shell);
size_t	size_allocation_expand(char *input, t_shell shell);
char	*detect_full_variable(char *input);

// Check.c
char	*valid_command(char *path, char *command, size_t *type);
char	*ft_ignore_str(char *str, char *ignore);

//Prompt.c
char	*get_command(char *input, t_shell *shell);

//Quotes.c
size_t	inside_quote(char c, char *quote);
char	*skip_space(char *input);

// Lexer.c
char	*lexer(char *input);

// Parser.c
size_t	parser(t_table *table, char **env, char *lexer);

#endif
