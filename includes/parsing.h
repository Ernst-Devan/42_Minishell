/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 07:57:21 by dernst            #+#    #+#             */
/*   Updated: 2025/06/20 12:42:25 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdlib.h>

# define NAME_MAX 255
# define ENV_MAX 32760
# define LIM "<>|"
# define SEP '\x1F'
# define SEP2 "\x1F"
# define EXPAND '\x1E'
# define RED "\001\e[0;36m\002"
# define BLUE "\001\e[0;91m\002"
# define WHITE "\001\e[0;37m\002"
# define CMD 0
# define LESSLESS 1
# define GREAT 2
# define PIPE 3
# define LESS 4
# define GREATGREAT 5
# define ERROR 6
# define E_MALLOC 2
# define SKIP 3

typedef struct s_shell
{
	size_t	status;
	char	**env;
	int		nb_cmd;
	int		error_code;
}	t_shell;

typedef struct s_cmd
{
	size_t	type;
	char	*path;
	char	**args;
	char	*str_in;
	char	*str_out;
	int		in;
	int		out;
}	t_cmd;

typedef struct s_lst_child
{
	int					pid;
	struct s_lst_child	*next;
}	t_lst_child;

typedef struct s_table
{
	t_cmd	*cmds;
	size_t	cmd_len;
}	t_table;

typedef struct s_expand
{
	size_t	i;
	size_t	j;
	size_t	alloc;
	char	*buffer;
}	t_expand;

// Redirection.command
char		**manage_redirection(t_cmd **cmd, char **split_cmd);
char		**skip_redirection(char **split_cmd);

char		*remove_quote(char *str);

// Parsing.c
size_t		parsing(t_shell *shell, t_table *table);

// Init.c
void		init_cmd(t_cmd *cmd, int nb_cmd);
size_t		init_table(t_table **table, char **input, int nb_cmd);

//Quotes.c
char		**remove_quotes(char **splited_cmd);

// Free.c
void		free_lstr(char **lstr);
void		free_cmds(t_table tabl);
void		free_table(t_table table);

// Env.c
char		*find_env(char *str, char **env);

//Lexical.c
int			lexical(t_shell *shell, char **input, t_table **table);

// Command_split.c
size_t		count_split(char *input, char c);
size_t		nb_letter(char *input, char c);
char		**split_cmd(char *input, char c);

// Space.c
size_t		manage_space(char **input);
char		*skip_first_space(char *variable);

// Utils.c
int			count_lstr(char **lstr);
int			ft_strlen_c(char *str, char delimiter);
size_t		check_delimiter(char c, char *delimiter);
void		display_lstr(char **lstr);
void		display_table(t_table table);
size_t		count_chars(char *s, char *cs);
size_t		ft_strccat(char *dest, char *src, char c);

// Expand.c
size_t		manage_expand(t_shell shell, char **input);
size_t		init_expand(t_expand *expand, char *input, t_shell shell);
size_t		size_allocation_expand(char *input, t_shell shell);
char		*detect_full_variable(char *input);

// Check.c
char		*valid_command(char *path, char *command, size_t *type);

//Prompt.c
size_t		get_command(t_shell *shell, char **input);

//Quotes.c
size_t		inside_quote(char c, char *quote);

// Lexer.c
size_t		lexer(char **input);

// Parser.c
size_t		parser(t_table *table, char **env, char *lexer);

size_t		quote_check(char *input);

#endif
