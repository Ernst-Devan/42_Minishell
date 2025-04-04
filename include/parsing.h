
#ifndef PARSING_H 
# define PARSING_H

typedef struct s_command {
    int  type;
    char *path;
    char **args;
} t_command;

t_command parsing(char **env);

#endif
