
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

int	export(t_cmd cmd, char ***env, t_shell *shell);
int	find_env_variable(char **env, char *str);
int	edit_variable_env(char ***env, char *data);
int	add_variable_env(char ***env, char *data);

int		cd(t_cmd cmd, char ***env);
int		echo(t_cmd command);
int		pwd(char **env);
int		unset(t_cmd cmd, char ***env);
void	ms_exit(t_cmd cmd, char **env, t_shell shell);
void	child_exit(char **env);


int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell);

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
void	useless_function2(int sig);


#endif
