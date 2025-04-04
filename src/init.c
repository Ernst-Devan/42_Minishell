#include "minishell.c"

t_command init_command(t_command command)
{
    command.path = NULL;
    command.args = NULL;
}
