#ifndef PIPE_H 
# define PIPE_H

#include "parsing.h"

/** 
 * This function uses pipes to redirect the input and output of built-in commands or binaries.  
 * Refer to "man dup2" and "man execve" for more details.
 * 
 * @param table A table struct containing the path and the command/binary used for execution. It executes only one binary or command.
 * @param in The input of the previous pipe (the read end of the previous pipe).
 * @param pipefd The read and write file descriptors of the current pipe.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
int	use_pipe(t_cmd command, int in, int pipefd[2], char ***pipe, t_shell *shell);

/** 
 * The main function for handling pipes.  
 * Refer to "man pipe" for more details.
 *
 * @param table A table struct containing the path and the command/binary used for execution. It executes only one binary or command.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
int	ms_pipe(t_table table, char ***pipe, t_shell *shell);

#endif