
#ifndef PARSING_H 
# define PARSING_H

#include <stdlib.h>

typedef struct s_status {
    size_t execution;
    size_t nb_cmd;
} t_status;

typedef struct s_command {
    size_t type;
    char *cmd;
    char **args;
    char *parameters;
    char *std_in;
    char *std_out;
    char *std_error;
} t_command;

t_command   *parsing(char **env);
void        display_table(t_command *cmds, int count);


#endif
