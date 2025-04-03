
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "unistd.h"
#include "minishell.h"

int main(int ac, char **argv, char **env)
{
    (void)ac;
    (void)argv;
    parsing(env);
}
