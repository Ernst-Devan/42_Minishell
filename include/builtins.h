
#ifndef BUILTINS_H 
# define BUILTINS_H

#include "parsing.h"

int	ms_cd(t_cmd command);
int	exec_builtins(t_table table, char ***env);
int	export(t_table table, char ***env);

#endif
