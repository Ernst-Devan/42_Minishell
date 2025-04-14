
#ifndef EXEC_H 
# define EXEC_H

#include "parsing.h"

/** 
 * This function executes the binary file provided to it.
 *
 * @param table A table struct containing the path and the command/binary used for execution. It executes only one binary or command.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
int	exec_bin(t_table table);

/** 
 * The main function for the execution part.
 *
 * @param table A table struct that contains the path and the command(s) / bin(s) used to execute the code.
 * @return On succes, these function return 0. On error, 1 is returned and errno is set appropriately  
 */
int	exec(t_table table, char **env);

int	export(t_table table, char **env);


#endif
