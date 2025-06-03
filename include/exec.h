
#ifndef EXEC_H 
# define EXEC_H

#include "parsing.h"

/** 
 * This function executes the binary file provided to it.
 *
 * @param table A table struct containing the path and the command/binary used for execution. It executes only one binary or command.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
int	exec_bin(t_table table, char **env);
int	exec_bin(t_table table, char **env);

/** 
 * The main function for the execution part.
 *
 * @param table A table struct that contains the path and the command(s) / bin(s) used to execute the code.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
t_shell	exec(t_table table, char ***env, t_shell shell);

int	export(t_cmd cmd, char ***env);
int	find_env_variable(char **env, char *str);
int	edit_variable_env(char ***env, char *data);
int	add_variable_env(char ***env, char *data);

int		cd(t_cmd cmd, char ***env);
int		echo(t_cmd command);
int		pwd(t_cmd cmd);
int		unset(t_cmd cmd, char ***env);
void	ms_exit(t_cmd cmd, char **env, t_shell *shell, t_table table);
int		env_builtin(char **env, t_cmd cmd);

int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell, t_table table);

char	*remove_consecutiv_slash(char *path);
char	*remove_dot_slash(char *path);
char	*remove_if_dotdot(char *path);

char	*update_pwd(char *pwd);
char	*get_pwd(char **env);
char	*build_pwd(char *pwd, char *path);
int		set_pwd(char *pwd, char ***env);

int	manage_ctrl_c_var(int val);
void	sig_hand(int sig);
int		useless_function(void);

int	open_heredoc(char *str, char **eof, char **name);
int	open_in_file(char *str);
void	heredoc(int	fd, char *eof);
int	open_in_heredoc_cmd(t_cmd *cmd, int *nb_files);
int	open_in_cmd(t_cmd *cmd);
int	manage_in(t_cmd *cmds, t_table table, int *nb_files);

int	manage_out(t_cmd *cmds, t_table table);
int	open_out_cmd(t_cmd *cmd);
int	open_out_file(char *str);
int	open_append(char *str);
void	close_fd(t_table table);

int	lexical_analyser(char *input);

#endif
